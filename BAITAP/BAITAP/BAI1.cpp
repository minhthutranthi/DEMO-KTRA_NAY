#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

struct Item {
    std::string Ten;
    int Trong_luong;
    int Gia_tri;
    int Phuong_an = 0; 

    double Gia_triPerTrong_luong() const {
        return static_cast<double>(Gia_tri) / Trong_luong;
    }
};

bool compare(const Item& a, const Item& b) {
    return a.Gia_triPerTrong_luong() > b.Gia_triPerTrong_luong();
}

int main() {
    std::ifstream infile("input.txt");

    if (!infile) {
        std::cerr << "Unable to open file";
        return 1;
    }

    int W, n;
    infile >> W >> n;

    std::vector<Item> items(n);

    for (int i = 0; i < n; ++i) {
        infile >> items[i].Ten >> items[i].Trong_luong >> items[i].Gia_tri;
    }

    infile.close();

    
    std::sort(items.begin(), items.end(), compare);

    int currentTrong_luong = 0;
    double totalGia_tri = 0;

    for (auto& item : items) {
        if (currentTrong_luong + item.Trong_luong <= W) {
            item.Phuong_an = 1; 
            currentTrong_luong += item.Trong_luong;
            totalGia_tri += item.Gia_tri;
        }
    }

  
    std::cout << "Danh sach do vat duoc chon:" << std::endl;
    for (const auto& item : items) {
        if (item.Phuong_an > 0) {
            std::cout << item.Ten << " - So luong: " << item.Phuong_an
                << ", Trong luong : " << item.Trong_luong
                << ", Gia tri: " << item.Gia_tri << std::endl;
        }
    }
    std::cout << "Tong gia tri: " << totalGia_tri << std::endl;

    return 0;
}
