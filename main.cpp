// Project UID db1f506d06d84ab787baf250c265e24e
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <cmath>
#include "csvstream.h"

using namespace std;

class classifier{
    public:
        void training_stream(csvstream &csvin, int argc){
            map<string, string> input;
            if (argc == 4) {
                cout << "training data:" << endl;
            }
            while(csvin >> input){
                    if (labels.find(input["tag"]) == labels.end()){
                        labels.insert({input["tag"], 1});
                    }
                    else{
                        labels[input["tag"]]++;
                    }
                    if (argc == 4) {
                        cout << "  label = " << input["tag"] << ", content = " 
                        << input["content"] << endl;   
                    }   
                    words_map_training(input["content"], input["tag"]);
            }
            cout << "trained on " << total_posts << " examples" << endl;
            vocab_size = words.size();
            /*
            if (argc == 4) {
                cout << "vocabulary size = " << vocab_size << endl; 
                cout << "classes:" << endl;
                cout.precision(3);
                for (auto i : labels) {
                    cout << i.first << ", " 
                    << i.second << " examples, log-prior = " 
                    << log(labels[i.first] / total_posts) << endl;
                }

                for (auto i : label_words) {
                    
                }
            }
            */
           if (argc == 4) {
               print_debug_classes_and_classifiers();
           }
           else {
               cout << endl;
           }
        }

        void words_map_training(const string &str, const string &label){
            total_posts++;
            istringstream source(str);
            string individual_words;
            set<string> unique_words;
            while(source >> individual_words){
                unique_words.insert(individual_words);
            }

            for(auto &i:unique_words){
                if(words.find(i) == words.end()){
                    words.insert({i, 1});
                }
                else{
                    words[i]++;
                }

                if(label_words.find({label, i}) == label_words.end()){
                    label_words.insert({{label, i}, 1});
                }
                else{
                    label_words[{label, i}]++;
                }
            }
        }

        void test_stream(csvstream &csvin2, int argc){
            /*
            cout << "test data:" << endl;
            map<string, string> input;
            while(csvin2 >> input){
                istringstream source(input["content"]);
                string individual_words;
                set<string> temp;
                while(source >> individual_words){
                    temp.insert(individual_words);
                }
                cout << "  correct = " << input["tag"] << ", predicted = ";
                if(find_label(temp, argc).first == input["tag"]){
                    string label = find_label(temp, argc).first;
                    double probability = find_label(temp, argc).second;
                    //cout << "  correct = " << input["tag"] << ", predicted = "
                    cout << label << ", log-probability score = " 
                    << probability << endl;
                    count1++;
                }
                count2++;
                cout << "  content = " << input["content"] << endl << endl;
            }
            cout << "performance: " << count1 << " / " 
            << count2 << " posts predicted correctly" << endl;
            */
            cout << "test data:" << endl;
            map<string, string> input;
            while(csvin2 >> input){
                istringstream source(input["content"]);
                string individual_words;
                set<string> temp;
                while(source >> individual_words){
                    temp.insert(individual_words);
                }
                cout << "  correct = " << input["tag"] << ", predicted = ";
                if(find_label(temp, argc) == input["tag"]){
                    count1++;
                }
                count2++;
                cout << "  content = " << input["content"] << endl << endl;
            }
            cout << "performance: " << count1 << " / " 
            << count2 << " posts predicted correctly" << endl;
        }
        
        void print_debug_classes_and_classifiers() {
            cout << "vocabulary size = " << vocab_size << endl; 
            cout << endl << "classes:" << endl;
            cout.precision(3);
            for (auto i : labels) {
                cout << "  " << i.first << ", " 
                << i.second << " examples, log-prior = " 
                << log(labels[i.first] / total_posts) << endl;
            }
            cout << "classifier parameters:" << endl << endl;
            for (auto i : label_words) {
                cout << "  " << i.first.first << ":" << i.first.second
                << ", count = " << i.second << ", log-likelihood = "
                << log(i.second/labels[i.first.first]) << endl;
            }
            cout << endl;
        }

        string find_label(set<string> bag_of_words, int argc) {
            double max_probability = -1000000000000;
            string label = "";
            for (auto &i : labels) {
                double current_probability = compute_log(bag_of_words, i.first, argc);
                if (current_probability > max_probability) {
                    max_probability = current_probability;
                    label = i.first;
                }
            }
            cout << label << ", log-probability score = " << max_probability << endl;
            return label;
        }

        double compute_log(set<string> bag_of_words, string label, int argc) {
            cout.precision(3);
            double sum_init = log(labels[label] / total_posts);
            double sum = sum_init;
            for (auto i : bag_of_words) {
                if (words.find(i) == words.end()) {
                    sum += log(1 / total_posts);
                    /*
                    if (argc == 4) {
                        cout << label << ":" << i << ", count = " 
                        << label_words[{label, i}] << ", log-likelihood = " 
                        << log(1 / total_posts) << endl;
                    }
                    */
                }
                else if (label_words.find({label,i}) == label_words.end()) {
                    sum += log(words[i] / total_posts);
                    /*
                    if (argc == 4) {
                        cout << label << ":" << i << ", count = " 
                        << label_words[{label, i}] << ", log-likelihood = " 
                        << log(words[i] / total_posts) << endl;
                    }
                    */
                }
                else {
                    sum += log(label_words[{label, i}] / labels[label]);
                    /*
                    if (argc == 4) {
                        cout << label << ":" << i << ", count = " 
                        << label_words[{label, i}] << ", log-likelihood = " 
                        << log(label_words[{label, i}] / labels[label]) << endl;
                    }
                    */
                }
            }
            //if (argc == 4) { cout << endl; }
            return sum;
        }

    private:
        double total_posts = 0;
        double vocab_size = 0;
        map<string, double> words;
        map<string, double> labels;
        map<pair<string, string>, double> label_words;
        int count1 = 0;
        int count2 = 0;
};

int main(int argc, char* argv[]){
    if (argc != 3 && argc != 4) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }
    string debug_line = "--debug";
    if (argc == 4 && (argv[3] != debug_line)) {
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return -1;
    }
    string training_filename = argv[1], user_filename = argv[2];
    ifstream is1(training_filename), is2(user_filename);
    if (!is1.is_open() || !is2.is_open()) {
        cout << "Error opening file: " << training_filename << endl;
        return -1;
    }
    csvstream train_csvin(argv[1]);
    csvstream user_csvin(argv[2]);
    classifier *c = new classifier; 
    c->training_stream(train_csvin, argc);
    c->test_stream(user_csvin, argc);
    delete c;
}