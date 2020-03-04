
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
using namespace std;

class buferCeneter{
private:
    vector<string> AllChanges;
    int obsAC = 0;
public:
    void addBuf(string buf){
        if(AllChanges.size() == obsAC) {
            AllChanges.push_back(buf);
            obsAC++;
        } else{
            AllChanges[++obsAC] = buf;
        }
    }
    string undo(){
        if(obsAC == 0){
            return AllChanges[obsAC];
        } else {
            return AllChanges[--obsAC];
        }
    }
    string undoUndo(){
        if(++obsAC<AllChanges.size()){
            return AllChanges[obsAC];
        } else{
            return AllChanges[--obsAC];
        }
    }
    int containSubstring(string patern){
        if(AllChanges[obsAC].find(patern)!=string::npos){
            return 1;
        }else{
            return 0;
        }
    }
};

class texteditor{
private:
    vector<int> lineLength;
    string buffer = "";
    fstream file;
    string paths;
    string pathl;
    int x = 0;
    int y = 0;
    int maxX = 0;
    int xline = 0;
    int lineL = 0;
    //char cursesString[9000];
    buferCeneter BC;
    std::map<std::string, std::string> entries;
public:
    void mainFoo(string ch) {
            if(ch == "<LEFT>") {
                if (x != 0 || y != 0) {
                    x--;
                    xline--;
                    if (xline + 1 == 0) {
                        y--;
                        lineL = lineLength[y];
                        xline = lineL;

                    }
                }
            }else if(ch == "<RIGHT>") {
                if (x + 1 <= maxX) {
                    x++;
                    xline++;
                    if (xline > lineL) {
                        xline = 0;
                        y++;
                        lineL = lineLength[y];
                    }
                }
            }else if(ch == "<UP>") {
                if (y > 0) {
                    if (lineLength[y - 1] < xline) {
                        y--;
                        x -= xline + 1;
                        lineL = lineLength[y];
                        xline = lineL;
                    } else {
                        y--;
                        x = x - lineLength[y] - 1;
                        lineL = lineLength[y];
                    }
                }
            }else if(ch == "<DOWN>") {
                if (y < lineLength.size() - 1) {
                    y++;
                    if (xline > lineLength[y]) {
                        x = x + (lineL - xline) + lineLength[y] + 1;
                        lineL = lineLength[y];
                        xline = lineL;
                    } else {
                        x = x + lineLength[y - 1] + 1;
                        lineL = lineLength[y];
                    }
                }
            }else if(ch == "<BACKSPACE>") { //backspace trzeba resize
                if (x > 0) {
                    buffer.erase(x - 1, 1);
                    if (xline == 0 && x > 0) {
//                            y--;
//                            lineL = lineLength[y]+1;
//                            xline = lineL;
                        int yKeep = --y;
                        int xlKeep = lineLength[y];
                        resizeX();
                        y = yKeep;
                        xline = xlKeep;
                        x = 0;
                        for (int i = 0; i < y; ++i) {
                            x += lineLength[i];
                        }
                        x += xline;
                        lineL = lineLength[y];
                    } else {
                        lineL--;
                        x--;
                        xline--;
                        maxX--;
                    }
                }
            }else if(ch == "<ENTER>") { // enter
                BC.addBuf(buffer);
                buffer.insert(x, "\n");

                if (lineLength.size() == y) {
                    (lineLength.push_back(lineL));
                } else {
                    (lineLength[y] = lineL);
                }
                xline = 0;
                lineL = 0;
                x++;
                y++;
                maxX++;
            }else {
                if (ch == " ") {
                    BC.addBuf(buffer);
                }
                buffer.insert(x, ch);
                clear();
                x++;
                xline++;
                maxX++;
                lineL++;
                if (y < lineLength.size()) {
                    lineLength[y] = lineL;
                } else {
                    lineLength.push_back(lineL);
                }
            }
    }
    void refreshR(){
        printw("%s\n", buffer.c_str());
        refresh();
    }
    void undo(){
        buffer = BC.undo();
        resizeX();
    }
    void undoUndo(){
        buffer = BC.undoUndo();
        resizeX();
    }
    void saving(){
        file.open(paths, fstream::out);
        file << buffer;
        file.close();
    }
    void jumpToline(string line){
        int chosenL = stoi(line) - 1;
        x = 0;
        y = chosenL;
        if (chosenL < lineLength.size()) {
            for (int i = 0; i < chosenL; i++) x += (lineLength[i]+1);
            lineL = lineLength[chosenL];
            xline = 0;
        }
    }
    void load(){
        ostringstream loadbuf;
        file.open(pathl, fstream::in);
        loadbuf << file.rdbuf();
        buffer = loadbuf.str();
        file.close();
        resizeX();
    }
    void resizeX(){
        int sizeStr = buffer.size();
        xline = 0;
        y = 0;
        maxX = 0;
        for(int i = 0; i < sizeStr; i++){
            if(buffer[i] == '\n'){
                if (lineLength.size() > y-1) {
                    lineLength[y] = xline;
                } else{
                    lineLength.push_back(xline);
                }
                y++;
                xline = 0;
            } else{
                xline++;
            }
            maxX++;
        }
        lineLength[y] = xline;
        lineL = xline;
        x = maxX;
    }
    void setPaths(string fileName){
        paths = fileName;
    }
    void setPathl(string fileName){
        pathl = fileName;
    }

};


//int main() {
//    string paths;
//    string pathl;
//
//    paths = "/home/ciszek/PO/textbuf.txt";
//    pathl = "/home/ciszek/PO/testload.txt";
//    texteditor editor();
//
//    return 0;
//}
