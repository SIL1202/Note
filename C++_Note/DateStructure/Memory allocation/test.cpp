#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T> class Student {
private:
  std::string name;
  size_t subject_n;
  std::vector<T> subject_grade;
  T total = 0;

public:
  Student() : name(""), subject_n(0) {}
  Student(std::string s) : name(s) {}

  friend std::istream &operator>>(std::istream &in, Student<T> &obj) {
    if (obj.subject_n == 0) {
      throw std::runtime_error("Subject count is not initialized!");
    }

    in >> obj.name;
    obj.total = 0;
    for (int i = 0; i < obj.subject_n; i++) {
      in >> obj.subject_grade[i];
      obj.total += obj.subject_grade[i];
    }
    return in;
  }

  friend std::ostream &operator<<(std::ostream &out, const Student<T> &obj) {
    out << obj.name << " - Scores: ";

    for (const auto &grade : obj.subject_grade) {
      out << grade << " ";
    }
    out << "| Total: " << obj.Total() << " | Average: " << obj.Average();
    return out;
  }

  bool operator>(const Student &other) const {
    return this->total > other.total;
  }

  void set_subject_num(int m) {
    subject_n = m;
    subject_grade.resize(m);
  }

  double Total() const { return static_cast<double>(total); }

  double Average() const { return static_cast<double>(total) / subject_n; }

  T getSubjectGrade(int index) const { return subject_grade[index]; }
};

class StudentManager {
private:
  std::vector<Student<double>> students;

public:
  StudentManager(size_t n) : students(n) {}

  void setSubjects(int m) {
    for (auto &student : students) {
      student.set_subject_num(m);
    }
  }

  void input() {
    for (auto &student : students) {
      std::cin >> student;
    }
  }

  void sortStudents() {
    std::sort(students.begin(), students.end(),
              [](const Student<double> &a, const Student<double> &b) {
                return a > b;
              });
  }

  void displayStudents() const {
    for (size_t i = 0; i < students.size(); i++) {
      std::cout << i + 1 << ". " << students[i] << std::endl;
    }
  }

  void rankingBySubject(int n) {
    std::sort(students.begin(), students.end(),
              [&](const Student<double> &a, const Student<double> &b) {
                return a.getSubjectGrade(n - 1) > b.getSubjectGrade(n - 1);
              });
    std::cout << "\nRanking by Subject " << n << ":\n";
    displayStudents();
  }

  void FilteredStudents(int s1, int s2) {
    std::vector<Student<double>> temp;
    std::copy_if(students.begin(), students.end(), std::back_inserter(temp),
                 [&](const Student<double> &a) {
                   return a.Total() >= s1 && a.Total() <= s2;
                 });

    std::cout << "Filtered Students (Total Score between " << s1 << " and "
              << s2 << "):\n";
    for (size_t i = 0; i < temp.size(); i++) {
      std::cout << i + 1 << ". " << temp[i] << std::endl;
    }
  }
};

int main() {
  size_t n, m;
  std::cout << "Enter the number of students and subjects: ";
  std::cin >> n >> m;

  StudentManager manager(n); // 建立 StudentManager
  manager.setSubjects(m);    // 設置科目數

  std::cout << "Enter the name and scores for each student:\n";
  manager.input(); // 輸入學生資料

  manager.sortStudents(); // 按總分排序

  std::cout << "\nStudent List (sorted by total score):\n";
  manager.displayStudents(); // 顯示排序後的學生列表

  int subjectNumer;
  std::cout << "\nEnter the subject number to rank by: ";
  std::cin >> subjectNumer;
  manager.rankingBySubject(subjectNumer);

  int score1, score2;
  std::cout << "\nEnter the total score range to filter by (e.g., 300 350): ";
  std::cin >> score1 >> score2;
  manager.FilteredStudents(score1, score2);

  return 0;
}
