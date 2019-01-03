#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
using namespace std;
class File {
private:
    string file_name;
    string file_path;
public:
    File();
    File(string file_name);
    ~File() {}

    // 统计文档中有多少字符
    int CountCharacters();

    // 读取指定位置的字符
    char ReadCharacter(int pos);

    //重载［］能够从数据文件随机读写
    char operator[](int pos);

};

// 无参构造函数
// 用户输入文件名
// 文件目录默认在桌面
File::File(){
    cout << "Please input filename: ";
    cin >> file_name;
    file_path = "C:\\Users\\yezi1\\Desktop\\";
    file_path.append(file_name);
    file_path.append(".txt");
}

// 有参构造函数
// 文件目录默认在桌面
File::File(string file_name) {
    file_path = "C:\\Users\\yezi1\\Desktop\\";
    file_path.append(file_name);
    file_path.append(".txt");
}

// 统计文档中有多少字符
// 思路：逐行读取文档并统计字数，相加即得结果
int File::CountCharacters() {
    // 返回值
    int length_total = 0;
    string str;
    ifstream infile(file_path, ios::in);

    // 文件异常处理
    if(!infile){
        cerr << "Can't open file!" << endl;
    }
    else{
        // 逐行读取文档并统计字数，相加即得结果
        while(getline(infile, str)){
            length_total += str.length();
        }
        infile.close();
    }
    return length_total;
}

// 读取指定位置的字符
// 注：
// 1.不算换行符
// 2.但是空格与标点符号都算
// 3.从1开始
// 思路：
// 首先统计文档内容字数，判读是否越界。
// 其次逐行读取文档内容并储存到buffer中， 最后return buffer[pos - 1]即可
char File::ReadCharacter(int pos) {
    int total_length = CountCharacters();
    string buffer;
    string str;
    if(pos <= 0 || pos > total_length){
        cout << "Out of Range!" << endl;
    }
    else{
        ifstream infile(file_path, ios::in);
        if(!infile){
            cerr << "Can't open file!" << endl;
        }
        else{
            while(getline(infile, str)){
                buffer.append(str);
            }
            infile.close();
        }
        return buffer[pos - 1];
    }
}

// 重载［］能够从数据文件随机读写
char File::operator[](int pos) {
    char c = ReadCharacter(pos);
    return c;
}

int main() {
    int total_num;  // 文档所有字符数
    int j, luck_num;

    File f1("in");
    total_num = f1.CountCharacters();
    cout << "Total characters in file: " << total_num << endl;
    cout << "Character 1: " << f1.ReadCharacter(1) << endl;
    cout << "Character 648: " << f1.ReadCharacter(648) << endl;
    cout << "Character 649: " << f1.ReadCharacter(649) << endl;

    cout << "Overload Test: " << endl;
    cout << "Character 1: " << f1[1] << endl;
    cout << "Character 3: " << f1[3] << endl;
    cout << "Character 648: " << f1[648] << endl;


    // 一个小游戏：
    // 用户输入n次
    // 随机读n次文档内的内容
    cout << "Feeling Lucky?" << endl;
    cout << "How many times: ";
    cin >> luck_num;

    srand((unsigned)time(NULL));
    for(int i = 0; i < luck_num; i++){
        // 限定rand范围是[1, total_num]
        j = (rand() % total_num) + 1;
        cout << "character " << j << ": ";
        cout << f1[j] << endl;
    }

    return 0;
}