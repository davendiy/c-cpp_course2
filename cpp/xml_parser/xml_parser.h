// Created by David Zashkolny on 21.04.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#ifndef VECTOROFINT_XML_PARSER_H
#define VECTOROFINT_XML_PARSER_H

#include <fstream>
#include <string>
#include <vector>
#include <map>

#endif //VECTOROFINT_XML_PARSER_H


using namespace std;

class XmlTree{
public:
    XmlTree(){};
    XmlTree(string &name, const map<string, string> Attributes, vector<XmlTree> sons, string &text);
    ~XmlTree();

    string Name;
    map<string, string> Attributes;
    vector<XmlTree> sons;
    string text;

    string str(int tabs_amount);
};


string parseTagName(ifstream &file);
map<string, string> parseTagAttrs(ifstream &file);
string parseTagText(ifstream &file);
string parseTagEnd(ifstream &file);
void parse();
