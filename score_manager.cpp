#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;
//学生类
class Student
{
    private:
        string id; //
        string name;
        double chinese;
        double math;
        double english;
    public:
        Student() : chinese (0), math(0),english(0){}
        Student(string i,string n,double c,double m,double e) : id(i), name(n), chinese(c), math(m), english(e) {}
        string getId() const { return id;}
        string getName() const { return name;}
        double getChinese() const { return chinese;}
        double getMath() const { return math;}
        double getEnglish() const { return english;}
        double getTotal() const { return chinese + math + english; }
        double getAverage() const { return getTotal()/3.0;}
        void setChinese(double c){ chinese = c;}
        void setMath(double m){ math = m;}
        void setEnglish(double e){english = e;}
        void setName(const string& n) { name = n;}
        void setId(const string& i){ id = i;}
    //显示学生信息
        void display() const {
            cout << left << setw(12) << id
                 << setw(8) << name
                 << setw(8) << chinese
                 << setw(8) << math
                 << setw(8) << english
                 << setw(8) << getTotal()
                 << setw(8) << fixed << setprecision(1) << getAverage()
                 << endl;
        }
};
//成绩管理类
class ScoreManager{
    private:
        vector<Student> students;
        int findIndexById(const string& id) const {
            for (int i = 0 ; i < students.size(); i++){
                if (students[i].getId() == id)
                    return static_cast<int>(i);
            }
            return -1;
        }
    public:
        bool addStudent(const Student& stu){
            if (findIndexById(stu.getId()) != -1){
                cout << "错误：学号 " << stu.getId() << "已存在！" << endl;
                return false;
            }
            students.push_back(stu);
            cout << "成功添加学生：" << stu.getName() << "(学号：" << stu.getId() << ")" << endl;
            return true;
        }
        bool removeStudent(const string& id){
            int idx = findIndexById(id);
            if (idx == -1){
                cout << "错误：学号" << id << "不存在！" << endl;
                return false;
            }
            students.erase(students.begin() + idx);
            cout << "成功删除学号为：" << id << "学生" << endl;
            return true;
        }
        bool modifyStudent(const string& id){
            int idx =findIndexById(id);
            if(idx == -1){
                cout << "错误：学号" << id << "不存在！" << endl;
                return false;                
            }
            Student& stu = students[idx];
            string newName;
            double ch, ma, en; 
            cout << " 请输入新的名字（原："<< stu.getName() << "）：";
            cin >> newName;
            cout << " 请输入新的语文成绩（原："<< stu.getChinese() << "）：";
            cin >> ch;stu.setChinese(ch);
            cout << " 请输入新的数学成绩（原："<< stu.getMath() << "）：";
            cin >> ma;stu.setMath(ma);
            cout << " 请输入新的英语成绩（原："<< stu.getEnglish() << "）：";
            cin >> en;stu.setEnglish(en);
            cout << "修改成功"<< endl;
            return true;
        }
        void querById (const string& id) const{
            int idx = findIndexById(id);
            if (idx == -1){
                cout << ""<<id << ""<<endl;
                return ;
            }
            cout << "\n"<< endl;
            cout << left << setw(12)<<"学号"
                 << setw(12)<< "姓名"
                 << setw(8)<< "语文"
                 << setw(8)<<"数学"
                 << setw(8)<<"英语"
                 << setw(8)<<"总分"
                 << setw(8)<<"平均分"<<endl;
            cout << string(64,'-')<<endl;
            students[idx].display();
        }
        void displayAll()const{
            if (students.empty()){
                cout <<"当前没有学生信息。"<<endl;
                return;
            }
            cout << "\n所有学生成绩列表（按学号顺序）："<<endl;
            cout << left << setw(12)<<"学号"
                 << setw(12)<< "姓名"
                 << setw(8)<< "语文"
                 << setw(8)<<"数学"
                 << setw(8)<<"英语"
                 << setw(8)<<"总分"
                 << setw(8)<<"平均分"<<endl;
            cout << string(64,'-')<<endl;
            for (const auto& stu : students){
                stu.display();
            }
        }
        void sortByTotal(){
            if (students.empty()){
                cout <<""<<endl;
                return;
            }
            vector<Student> sorted = students;
            sort(sorted.begin(),sorted.end(),[](const Student &a,Student &b){
                return a.getTotal() > b.getTotal();
            });
             cout << "\n按总分从高到低排序："<<endl;
             cout << left << setw(12)<<"学号"
                 << setw(12)<< "姓名"
                 << setw(8)<< "语文"
                 << setw(8)<<"数学"
                 << setw(8)<<"英语"
                 << setw(8)<<"总分"
                 << setw(8)<<"平均分"<<endl;
             cout << string(64,'-')<<endl;
             for (const auto& stu : students){
                stu.display();
            }   
        }
        bool saveToFile(const string& filename) const{
            ofstream out(filename);
            if (!out){
                cout << "无法打开文件 "<< filename <<"进行保存！"<<endl;
                return false;
            }
            for (const auto& stu : students){
                out << stu.getId() <<","
                    << stu.getName() <<","
                    << stu.getChinese() <<","
                    << stu.getMath() <<","
                    << stu.getEnglish() <<",";
            }
            out.close();
            cout << "成功保存 " << students.size() << " 条记录到文件"<< filename <<endl;
            return true;
        }
        bool loadFromFile(const string& filename){
            ifstream in(filename);
            if (!in){
                cout << "文件" << filename << " 不存在，将创建新数据" <<endl;
                return false;
            }
            students.clear();
            string line;
            while(getline(in,line)){
                size_t p1 = line.find(',');
                size_t p2 = line.find(',', p1 + 1);
                size_t p3 = line.find(',', p2 + 1);
                size_t p4 = line.find(',', p3 + 1);
                if (p1 == string:: npos|| p2 == string::npos || p3 == string::npos || p4 == string::npos)
                    continue;
                string id = line.substr(0, p1);
                string name = line.substr(p1 + 1, p2 - p1 -1);
                double ch = stod(line.substr(p2+1,p3-p2-1));
                double ma = stod(line.substr(p3+1,p4-p3-1));
                double en = stod(line.substr(p4+1));
                students.emplace_back(id,name,ch,ma,en);
            }
            in.close();
            cout << "成功从文件 " << filename << " 加载" << students.size() << " 条记录" << endl;
            return true;
        }

};
void showMenu(){
    cout << "\n====== 学生成绩管理器 ======" << endl;
    cout << "1. 添加学生" << endl;
    cout << "2. 删除学生" << endl;
    cout << "3. 修改学生信息" << endl;
    cout << "4. 查询学生（按学号）" << endl;
    cout << "5. 显示所有学生" << endl;
    cout << "6. 按总分排序并显示" << endl;
    cout << "7. 保存数据到文件" << endl;
    cout << "8. 从文件加载数据" << endl;
    cout << "0. 退出" << endl;
    cout << "请选择操作：";
}
int main (){
    ScoreManager manager;
    string filename = "students.csv";
    manager.loadFromFile(filename);
    int choice;
    string id, name;
    double ch, ma, en;
    while(true){
        showMenu();
        cin >> choice;
        switch(choice){
        case 1: // 添加
            cout << "请输入学号：";
            cin >> id;
            cout << "请输入姓名：";
            cin >> name;
            cout << "请输入语文成绩：";
            cin >> ch;
            cout << "请输入数学成绩：";
            cin >> ma;
            cout << "请输入英语成绩：";
            cin >> en;
            manager.addStudent(Student(id, name, ch, ma, en));
            break;
        case 2: // 删除
            cout << "请输入要删除的学生学号：";
            cin >> id;
            manager.removeStudent(id);
            break;
        case 3: // 修改
            cout << "请输入要修改的学生学号：";
            cin >> id;
            manager.modifyStudent(id);
            break;
        case 4: // 查询
            cout << "请输入要查询的学生学号：";
            cin >> id;
            manager.querById(id);
            break;
        case 5: // 显示所有
            manager.displayAll();
            break;
        case 6: // 排序显示
            manager.sortByTotal();
            break;
        case 7: // 保存
            manager.saveToFile(filename);
            break;
        case 8: // 加载
            manager.loadFromFile(filename);
            break;
        case 0:
            cout << "谢谢使用，再见！" << endl;
            return 0;
        default:
            cout << "无效选择，请重新输入！" << endl;
            break;
        }
    }
    return 0;
}