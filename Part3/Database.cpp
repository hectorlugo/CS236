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

//Uses the parser
Database::Database(string fileName_in, string fileName_out) : parser(fileName_in, fileName_out)
{
	Schemes = parser.getDatalog().getSchemes();
	Facts = parser.getDatalog().getFacts();
	Queries = parser.getDatalog().getQueries();
	outfile.open(fileName_out);
	createRelations();
	toString();
	outfile << "Query Evaluation" << endl << endl;
	evalQueries();
	outfile.close();
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

void Database::evalQueries()
{
	Relation relation;
	map<string, int> variables;
	map<int, string> variablePos;
	for (int i = 0; i < Queries.size(); i++){
		if (relations.count(Queries[i].getData())){
			relation = relations[Queries[i].getData()];
			for (int j = 0; j < Queries[i].getParameterList().size(); j++){
				string value = Queries[i].getParameterList().at(j).getValue();
				if (value[0] == '\''){
					relation.select(j, value);
				}
				else{
					if (variables.count(value) > 0){
						relation.select(j, variables[value]);
					}
					variables.insert(pair<string, int>(value, j));
					if (variables.size() > variablePos.size()){
						variablePos.insert(pair<int, string>(j, value));
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
			relation.rename(variablePos);
			relation.toString(outfile);
			outfile << endl;
		}
		variables.clear();
		variablePos.clear();
	}
}

void Database::toString()
{
	outfile << "Scheme Evaluation" << endl << endl << "Fact Evaluation" << endl << endl;

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