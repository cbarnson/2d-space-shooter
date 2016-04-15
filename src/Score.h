#ifndef SCORE_H
#define SCORE_H

#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <fstream>
#include <istream>
#include <ostream>
#include <memory>
#include <iostream>

struct scorePair {
   scorePair() {
      _name = "---";
      _score = 0;
   }
   scorePair(std::string name, int score) {
      _name = name;
      _score = score;
   }
   std::string _name;
   int _score;
};

class Score {
  public:
  Score(std::string filename) : _filename(filename) {
      
   }
   
   ~Score() {
      _data.clear();
   }   

   inline void update() {
      std::ofstream fout(_filename.c_str());
      if (fout.is_open()) {
	 std::cout << "out file is open" << std::endl;
	 for (unsigned int i = 0; i < _data.size(); i++) {
	    fout << _data[i]->_name << " " << _data[i]->_score << "\n";
	 }
	 fout.close();
      }
      else {
	 std::cout << "error outputting score info" << std::endl;
      }
   }
   
   inline void readPrev() {
      std::ifstream fin(_filename.c_str());      
      if (fin.is_open()) {
	 std::cout << "in file is open\n";
	 for (unsigned int i = 0; i < _data.size(); i++) {
	    if (!fin.eof()) {
	       std::cout << "reading value" << std::endl;
	       fin >> _data[i]->_name >> _data[i]->_score;	       
	    }
	 }
	 fin.close();
      }
      else {
	 std::cout << "error opening in file" << std::endl;
      }
   }   
   inline void swapWithMin(std::string name, int score) {
      _data[2]->_name = name;
      _data[2]->_score = score;
   }
   inline void sortRecords() {
      std::sort(_data.begin(), _data.end(),
		[](const std::shared_ptr<scorePair>& a, const std::shared_ptr<scorePair>& b) {
		   return a->_score > b->_score;
		});
   }   
   inline void init() {
      addEmptyPair();
      addEmptyPair();
      addEmptyPair();
   }
   // get methods
   inline int getMin() const {
      return _data[2]->_score;
   }
   inline std::string getName(int index) const {
      return _data[index]->_name;
   }
   inline int getScore(int index) const {
      return _data[index]->_score;
   }
   // some add functions
   inline void addEmptyPair() {
      _data.push_back(std::make_shared<scorePair> ());
   }   
   inline void addPair(std::string name, int score) {
      _data.push_back(std::make_shared<scorePair> (name, score));
   }
   
  private:
   std::string _filename;
   std::vector< std::shared_ptr<scorePair> > _data;


   
   /*
  public:
   Score(std::string filename);
   ~Score();
   
   void readFrom();
   void writeTo();
   
   bool isNewRecord(int);
   void replaceRecord(std::string, int);
   void sortRecords();
   
  private:
   std::vector< std::pair<std::string, int> > _data;
   std::string *_filename;

   void createNew();
   */
};



#endif
