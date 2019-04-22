// Created by David Zashkolny on 21.04.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "xml_parser.h"



XmlTree::XmlTree(string &name, const map<string, string> Attributes, vector<XmlTree> sons, string &text)
    :Name(""){
    Name = name;
    this->Attributes = Attributes;
    this->sons = sons;
    this->text = text;
}


XmlTree::~XmlTree() {
    Attributes.clear();
    Name.clear();
    sons.clear();
}


void parse(ifstream &file, XmlTree* &tree) {
    char symbol = ' ';
    string name = "";
    map<string, string> attrs;
    vector<XmlTree> sons;
    string text = "";
    string end_name = "";

    while (file >> symbol){
        streampos pos = file.tellg();

        file.seekg((int) file.tellg() - 1);
        end_name = parseTagEnd(file);
        if (!end_name.empty() && end_name == tree->Name){
            tree->text += text;
            return;
        } else if (!end_name.empty()){
            throw 0;
        }

        file.seekg(pos);

        if (symbol == '<'){
            tree->text += text;
            text = "";
            if (file >> symbol && symbol != '/'){
                file.seekg((int) pos - 1);
                name = parseTagName(file);
                file.seekg((int) pos - 1);
                attrs = parseTagAttrs(file);

                text = parseTagText(file);

                end_name = parseTagEnd(file);

                if (!name.empty() && !end_name.empty() && name == end_name){
                    vector<XmlTree> tmp;
                    string tmp_text = text;
                    XmlTree tmp_tree = XmlTree(name, attrs, tmp, tmp_text);
                    text = "";
                    tree->sons.push_back(tmp_tree);
                    continue;
                }
                if (end_name.empty()){
                    vector<XmlTree> tmp;
                    string tmp_text = text;
                    XmlTree *tmp_tree = new XmlTree(name, attrs, tmp, tmp_text);
                    text = "";
                    parse(file, tmp_tree);
                    tree->sons.push_back(*tmp_tree);
                }
            }


        } else {
            text += symbol;
        }

    }
    tree->text += text;
}

string parseTagName(ifstream &file){
    char symbol = ' ';
    string result = "";
    if (file >> symbol){
        if (symbol != '<'){
            throw 1;
        }

        while (file >> symbol && symbol != ' ' && symbol != '>'){
            if (symbol == '/'){
                continue;
            }

            result += symbol;
        }
        if (file.fail() && !file.eof()){
            throw 2;
        }
        return result;
    } else {
        throw 3;
    }

}


map<string, string> parseTagAttrs(ifstream &file){
    char symbol = ' ';
    bool flag_read_attr_name = false;
    bool flag_read_attr_value = false;
    map<string, string> result;
    if (file >> std::noskipws >> symbol){
        if (symbol != '<'){
            return result;
        }
        while (file >> std::noskipws >> symbol && symbol != ' ' and symbol != '>' && symbol != '/'){}

        if (file.fail()){
            throw 4;
        }

        if (symbol == '>' || symbol == '/') {
            return result;
        }

        flag_read_attr_name = true;
        string tmp_name = "";
        string tmp_value = "";
        while (file >> std::noskipws >> symbol && symbol != '>'){

            if (flag_read_attr_name && symbol != '='){      // read attribute name
                tmp_name += symbol;

            } else if (flag_read_attr_name) {                // end of attribute name
                flag_read_attr_name = false;
                flag_read_attr_value = true;

            } else if (flag_read_attr_value && symbol == '"'){
                continue;
            } else if (flag_read_attr_value && symbol != ' '){   // read attribute value
                tmp_value += symbol;

            } else if (flag_read_attr_value){                    // end of attribute value
                flag_read_attr_value = false;
                flag_read_attr_name = true;
                result[tmp_name] = tmp_value;
                tmp_name = "";
                tmp_value = "";
            }
        }
        if (!tmp_name.empty()){
            result[tmp_name] = tmp_value;
        }
        if (file.fail()){
            throw 5;
        }
    }

    if (file.fail()){
        throw 6;
    }
    return result;
}


string parseTagText(ifstream &file){
    char symbol = ' ';
    string result = "";
    while (file >> symbol && symbol != '<'){
        if (symbol == '\n') continue;
        result += symbol;
    }
    if (file.fail()){
        throw 7;
    }

    file.seekg((int) file.tellg() - 1);
    return result;
}


string parseTagEnd(ifstream &file){
    char symbol = ' ';
    string result = "";
    streampos prev_pos = file.tellg();
    if (file >> symbol && symbol == '<'){
        if (file >> symbol && symbol == '/') {
            while (file >> symbol && symbol != '>') {
                result += symbol;
            }
            if (file.fail()) {
                throw 8;
            }
        }
    }
    if (file.fail()){
        throw 9;
    }

    if (symbol != '>'){
        file.seekg(prev_pos);
    }
    return result;
}


string XmlTree::str(int tabs_amount) {
    string result = "";
    for (int i = 0; i < tabs_amount; i++){
        result += ' ';
    }
    result += "Node " + Name + " with attrs: ";
    for (map<string, string>::iterator itr = Attributes.begin(); itr != Attributes.end(); ++itr){
        result += " " + itr->first + "=" + itr->second;
    }

    result += " and text: " + text;
    for (vector<XmlTree>::iterator itr = sons.begin(); itr != sons.end(); ++itr){
        result += "\n" + itr->str(tabs_amount + 4);
    }
    return result;
}


int main(){
    ifstream test_file("/home/davidas/Документы/univer/c-cpp_course2/cpp/xml_parser/xml_text.xml", ios::in);
    XmlTree *test = new XmlTree;

    test->Name = "Root";
    parse(test_file, test);

    ifstream test_file2("/home/davidas/Документы/univer/c-cpp_course2/cpp/xml_parser/xml_text2.xml", ios::in);
    parse(test_file2, test);
    std::cout << test->str(0);
}
