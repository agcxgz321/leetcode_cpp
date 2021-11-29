#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;

void split(const string& src, const string& separator, vector<string>& dest) {
    string str = src;
    string substring;
    string::size_type start = 0, index;
    dest.clear();
    index = str.find_first_of(separator, start);
    do {
        if (index != string::npos) {
            substring = str.substr(start, index - start);
            dest.push_back(substring);
            start = index + separator.size();
            index = str.find(separator, start);
            if (start == string::npos) break;
        }
    }while(index != string::npos);
    substring = str.substr(start);
    dest.push_back(substring);
}

bool exist_SAM(const string& str) {
    int n = str.find("XT:A:U");
    return n != string::npos;
}

void count_chr_(string& str, int* chr_num) {
    if (str.find("chr") != string::npos) {
        string s = str.substr(3);
        // int x = stoi(s);
        if (s.find_first_of("xyzXYZ") != string::npos) return;
        int x;
        stringstream ss;
        ss << s;
        ss >> x;
        chr_num[x - 1]++;
    }

}

void count_ACGT(string& str, int* num) {
    int nsize = str.size();
    for (int i = 0; i < nsize; i++) {
        if (str[i] == 'A') num[0]++;
        else if (str[i] == 'C') num[1]++;
        else if (str[i] == 'G') num[2]++;
        else if (str[i] == 'T') num[3]++;
    }
}

void count_MDI(string& str, int* num) {
    string::size_type start = 0, index;
    index = str.find_first_of("MDI", start);
    while (index != string::npos) {
        string s = str.substr(start, index-start);
        int x;
        stringstream ss;
        ss << s;
        ss >> x;
        if (str[index] == 'M') num[0]++;
        else if (str[index] == 'D') num[1]++;
        else if (str[index] == 'I') num[2]++;
        start = index + 1;
        index = str.find_first_of("MDI", start);
    }
}

void count_ACGT_MD(string& str, int* num) {
    string::size_type n = str.find("MD:Z:");;
    if (n != string::npos && n == 0) {
        n = str.find('^', n);
        do{
            if (str[n + 1] == 'A') num[0]++;
            else if (str[n + 1] == 'C') num[1]++;
            else if (str[n + 1] == 'G') num[2]++;
            else if (str[n + 1] == 'T') num[3]++;
            n = n + 2;
            n = str.find('^', n);
        } while (n != string::npos);
    }
}

int main() {
    ifstream myfile("C:\\C++刷题\\question1\\Question1.sam");
    ofstream outfile("C:\\C++刷题\\question1\\Question1.csv");
    if (!myfile.is_open()) {
        cout << "未成功点开文件" << endl;
    }

    string temp;
    char a;
    int num_SAM = 0;
    int chr_num[22] = {0};
    int chr_total = 0;
    int ACGT_num[4] = {0};
    int ACGT_total = 0;
    int MDI_num[3] = {0};
    int MDI_total;
    int ACGT_MD_num[4];
    int ACGT_MD_total;

    while (getline(myfile, temp)) {
        if (exist_SAM(temp)) {
            num_SAM++;
            vector<string> str;
            string separator = "	";
            split(temp, separator, str);
            count_chr_(str[2], chr_num);
            count_ACGT(str[9], ACGT_num);
            count_MDI(str[5], MDI_num);
            count_ACGT_MD(str[16], ACGT_MD_num);
        }
    }



    outfile<<"ch1-22的行数"<<"\n";
    for (int i = 0; i < 22; i++) {
        outfile<<"ch"<<i+1<<","<<chr_num[i]<<"\n";
        chr_total += chr_num[i];
    }
    outfile<<"Total"<<","<<chr_total<<endl;

    outfile<<"A、C、G、T分别出现的次数"<<"\n";
    outfile<<"A"<<","<<ACGT_num[0]<<"\n";
    outfile<<"C"<<","<<ACGT_num[1]<<"\n";
    outfile<<"G"<<","<<ACGT_num[2]<<"\n";
    outfile<<"T"<<","<<ACGT_num[3]<<"\n";
    for (int i = 0; i < 4; i++) {
         ACGT_total += ACGT_num[i];
    }
    outfile<<"Totol"<<","<<ACGT_total<<endl;

    outfile<<"M、D、I 分别的频次\n";
    outfile<<"M,"<<MDI_num[0]<<"\n";
    outfile<<"D,"<<MDI_num[1]<<"\n";
    outfile<<"I,"<<MDI_num[2]<<"\n";
    for (int i = 0; i < 3; i++) {
        MDI_total += MDI_num[i];
    }
    outfile<<"Total,"<<MDI_total<<endl;

    outfile<<"\"^\"后面ACGT分别的次数\n";
    outfile<<"A,"<<ACGT_MD_num[0]<<"\n";
    outfile<<"C,"<<ACGT_MD_num[1]<<"\n";
    outfile<<"G,"<<ACGT_MD_num[2]<<"\n";
    outfile<<"T,"<<ACGT_MD_num[3]<<"\n";
    for (int i = 0; i < 4; i++) {
        ACGT_MD_total += ACGT_MD_num[i];
    }
    outfile<<"Total,"<<ACGT_MD_total<<endl;

    myfile.close();
    outfile.close();
    return 0;
}