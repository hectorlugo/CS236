#include "Database.h"

using namespace std;

string printDatabase(vector<string> temp)
{
	stringstream output;
	for (int i = 0; i < temp.size(); i++){
		output << "(" << temp[i] << ")" << " ";
	}
	return output.str();
}

Database::Database(string fileName_in, string fileName_out) : parser(fileName_in, fileName_out)
{
	size = -1;
	Schemes = parser.getDatalog().getSchemes();
	Facts = parser.getDatalog().getFacts();
	Rules = parser.getDatalog().getRules();
	Queries = parser.getDatalog().getQueries();
	outfile.open(fileName_out);
	createRelations();
	outfile << "Scheme Evaluation" << endl << endl << "Fact Evaluation" << endl << endl;
	toString();
	outfile << "Rule Evaluation" << endl << endl;
	int i = 0;
	while (size != getSize()){
		i++;
		size = getSize();
		evaluateRules();
	}
	outfile << endl << "Converged after " << i << " passes through the Rules." << endl << endl;
	toString();
	outfile << "Query Evaluation" << endl << endl;
	evalQueries();
	outfile.close();
}

int Database::getSize()
{
	int count = 0;
	for (auto& rel : relations){
		count += rel.second.getTuples().size();
	}
	return count;
}

void Database::createRelations()
{
	parseSchemes();
	parseFacts();
}

void Database::parseSchemes()
{
	Relation rel;
	for (int i = 0; i < Schemes.size(); i++){
		rel.setName(Schemes[i].getData());
		setRelationScheme(rel, i);
		relations.insert(pair<string, Relation>(rel.getName(), rel));
		rel.clearTupScheme();
	}
}

void Database::setRelationScheme(Relation& relation, int i)
{
	for (int j = 0; j < Schemes.at(i).getParameterList().size(); j++){
		relation.addSchemeAtt(parser.getDatalog().getSchemes().at(i).getParameterList().at(j).getValue());
	}
}

void Database::parseFacts()
{
	Tuple tup;
	for (int i = 0; i < Facts.size(); i++){
		if (relations.count(Facts[i].getData())){
			setTupleAttributeValues(tup, i);
			relations[Facts[i].getData()].addTuple(tup);
			tup.clear();
		}
	}
}

void Database::setTupleAttributeValues(Tuple& tuple, int i)
{
	for (int j = 0; j < Facts[i].getParameterList().size(); j++){
		tuple.addAttValue(Facts.at(i).getParameterList().at(j).getValue());
	}
}

bool compare(const Relation& relation1, const Relation& relation2)
{
	return relation1.getName() < relation2.getName();
}

void forEachParameterSelect(vector<Parameter>& paramList, Relation& r, int& j, map<string, int>& variables, vector<int>& variablePos, vector<string>& variableNames)
{
	string value;
	for (int k = 0; k < paramList.size(); k++){
		value = paramList[k].getValue();
		if (value[0] == '\''){
			r.select(k, value);
		}
		else{
			if (variables.count(value) > 0){
				r.select(j, variables[value]);
			}
			variables.insert(pair<string, int>(value, k));
			if (variables.size() > variablePos.size()){
				variableNames.push_back(value);
				variablePos.push_back(k);
			}
		}
	}
}

void setHeadVariables(vector<string>& schemeAttributes, Relation& r, vector<Parameter>& headParams, string& value, map<string, int>& variables, vector<int>& variablePos, vector<string>& variableNames)
{
	schemeAttributes = r.getScheme().getAttributes();
	for (int j = 0; j < headParams.size(); j++){
		value = headParams[j].getValue();
		for (int k = 0; k < schemeAttributes.size(); k++){
			if (value == schemeAttributes[k]){
				variables.insert(pair<string, int>(value, k));
				if (variables.size() > variablePos.size()){
					variableNames.push_back(value);
					variablePos.push_back(k);
				}
			}
		}
	}
}

void Database::evaluateRules()
{
	Relation r;
	map<string, int> variables;
	vector<int> variablePos;
	vector<string> variableNames;
	string head;
	vector<Parameter> headParams;
	queue<Relation> intermediate;
	vector<Predicate> predList;
	vector<Parameter> paramList;
	vector<string> schemeAttrs;
	string value;
	
	for (int i = 0; i < Rules.size(); i++){
		head = Rules[i].getRulePred().getData();
		headParams = Rules[i].getRulePred().getParameterList();
		predList = Rules[i].getRulePredicateList();
		for (int j = 0; j < predList.size(); j++){
			if (relations.count(predList[j].getData())){
				r = relations[predList[j].getData()];
				paramList = predList[j].getParameterList();
				forEachParameterSelect(paramList, r, j, variables, variablePos, variableNames);
			}
			r.project(variablePos);
			r.rename(variableNames);
			intermediate.push(r);
			variables.clear();
			variablePos.clear();
			variableNames.clear();
		}

		r = intermediate.front();
		intermediate.pop();

		while (!intermediate.empty()){
			r.join(intermediate.front());
			intermediate.pop();
		}

		setHeadVariables(schemeAttrs, r, headParams, value, variables, variablePos, variableNames);
		r.project(variablePos);
		r.rename(variableNames);
		Rules[i].toString();
		r.setName(head);

		if (relations.count(r.getName())){
			outfile << Rules[i].toString() << endl;
			relations[r.getName()].relationUnion(r, outfile);
		}
		variables.clear();
		variablePos.clear();
		variableNames.clear();
	}
}

void Database::evalQueries()
{
	Relation relation;
	map<string, int> variables;
	vector<int> variablePos;
	vector<string> variableNames;
	vector<Parameter> paramList;
	string value;
	for (int i = 0; i < Queries.size(); i++){
		if (relations.count(Queries[i].getData())){
			relation = relations[Queries[i].getData()];
			paramList = Queries[i].getParameterList();

			for (int j = 0; j < paramList.size(); j++){
				value = paramList.at(j).getValue();

				if (value[0] == '\''){
					relation.select(j, value);
				}
				else{
					if (variables.count(value) > 0){
						relation.select(j, variables[value]);
					}
					variables.insert(pair<string, int>(value, j));

					if (variables.size() > variablePos.size()){
						variableNames.push_back(value);
						variablePos.push_back(j);
					}
				}
				relation.setName("select");
			}
		}
		qToString(i, relation.getTuples().size());

		if (relation.getTuples().size() > 0){
			relation.toString(outfile);
			relation.project(variablePos);
			relation.toString(outfile);
			relation.rename(variableNames);
			relation.toString(outfile);
			outfile << endl;
		}
		variables.clear();
		variablePos.clear();
		variableNames.clear();
	}
}

void Database::toString()
{
	for (auto& rel : relations){
		rel.second.toString(outfile);
		outfile << endl;
	}
}

void Database::qToString(int i, int matches)
{
	outfile << Queries[i].toString() << "? ";
	if (matches > 0){
		outfile << "Yes(" << matches << ")" << endl;
	}
	else{
		outfile << "No" << endl << endl;
	}
}