#include <iostream> 
#include <string> // std::string ve std::to_string için kullanılır.
#include <cmath> // sqrt, pow, M_PI gibi matematiksel fonksiyonlar için kullanılır.
#include <locale>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;


class Nokta {
private:
    double x = 0;
    double y = 0;
public:
    // Nokta sınıfının yapıcı metodları
    Nokta() {
        this->setX(0);
        this->setY(0);
    };

    Nokta(double x) {
        this->setX(x);
        this->setY(x);
    }

    Nokta(double x, double y) {
        this->setX(x);
        this->setY(y);
    }

    Nokta(const Nokta& nokta) {
        this->setX(nokta.x);
        this->setY(nokta.y);
    };

    Nokta(const Nokta& nokta, double ofset_x, double ofset_y) {
        this->setX(nokta.x + ofset_x);
        this->setY(nokta.y + ofset_y);
    };

    // Nokta sınıfının get ve set metodları
    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    void setX(double x) {
        this->x = x;
    }

    void setY(double y) {
        this->y = y;
    }

    void set(double x, double y) {
        this->setX(x);
        this->setY(y);
    }

    // Nokta sınıfının diğer metodları
    std::string toString() const {
        return "(" + std::to_string(this->getX()) + ", " + std::to_string(this->getY()) + ")";
    }

    void yazdir() const {
        std::cout << this->toString() << std::endl;
    }

};

class DogruParcasi {
private:
    Nokta nokta1;
    Nokta nokta2;
public:

    // DogruParcasi sınıfının yapıcı metodları
    DogruParcasi(const Nokta& nokta1, const Nokta& nokta2) {
        this->setP1(nokta1);
        this->setP2(nokta2);
    }

    DogruParcasi(const DogruParcasi& dogruParcasi) {
        this->setP1(dogruParcasi.nokta1);
        this->setP2(dogruParcasi.nokta2);
    }

    /*
        Orta noktaya, uzunluğa ve eğime dayalı olarak doğru parçası oluştur
        Bu kurucu metod, bir doğru parçası oluşturmak için kullanılır. İlk olarak, doğru parçasının orta noktası (ortaNokta) alınır.
        Ardından, bu orta nokta üzerinden geçen ve verilen uzunluğa (uzunluk) ve eğime (egim) sahip olan bir doğru parçası oluşturulur.
        Formül: x1 = ortaNokta.getX() - uzunluk / 2
                y1 = ortaNokta.getY() - uzunluk / 2 * egim
                x2 = ortaNokta.getX() + uzunluk / 2
                y2 = ortaNokta.getY() + uzunluk / 2 * egim
        Burada, x1 ve y1 çizginin başlangıç noktasının koordinatlarıdır, x2 ve y2 ise çizginin bitiş noktasının koordinatlarıdır.
        Bu formül, orta noktaya ve verilen uzunluğa ve eğime dayalı olarak doğru parçasının uç noktalarını hesaplamak için kullanılır.
    */
    DogruParcasi(const Nokta& ortaNokta, double uzunluk, double egim) {
        double x1 = ortaNokta.getX() - uzunluk / 2;
        double y1 = ortaNokta.getY() - uzunluk / 2 * egim;
        double x2 = ortaNokta.getX() + uzunluk / 2;
        double y2 = ortaNokta.getY() + uzunluk / 2 * egim;
        this->setP1(x1, y1);
        this->setP2(x2, y2);
    }


    // DogruParcasi sınıfının get ve set metodları
    Nokta getP1() const {
        return nokta1;
    }

    Nokta getP2() const {
        return nokta2;
    }

    void setP1(const Nokta& nokta1) {
        this->nokta1 = nokta1;
    }

    void setP2(const Nokta& nokta2) {
        this->nokta2 = nokta2;
    }

    void setP1(double x, double y) {
        this->nokta1.set(x, y);
    }

    void setP2(double x, double y) {
        this->nokta2.set(x, y);
    }

    // DogruParcasi sınıfının diğer metodları

    double uzunluk() const {
        // İki nokta arası uzaklık formülü
        return sqrt(pow(this->getP1().getX() - this->getP2().getX(), 2) + pow(this->getP1().getY() - this->getP2().getY(), 2));
    }

    Nokta kesisimNoktasi(const Nokta& nokta) const {
        // Çizginin eğimini hesapla (m1)
        double m1 = (this->getP1().getY() - this->getP2().getY()) / (this->getP1().getX() - this->getP2().getX());

        // Eğer çizgi dikeyse, sıfıra bölme hatasını önlemek için ayrıca işle
        if (std::isinf(m1)) {
            // Çizgi dikey olduğunda, kesişim noktasının x koordinatı getNokta1()'in x koordinatı ile aynıdır
            double x = this->getP1().getX();
            // Dikey çizginin denklemi kullanılarak kesişim noktasının y koordinatını bul
            double y = m1 * (x - this->getP1().getX()) + this->getP1().getY();
            return Nokta(x, y);
        }

        // Dikey olan çizginin eğimini hesapla (m2)
        double m2 = -1.0 / m1;

        // Kesişim noktasının x koordinatını hesapla
        // Bu adımda, iki çizgi arasındaki kesişim noktasının x koordinatını bulmak için kullanılan formülü uyguluyoruz.
        // Formül: x = (m1 * x1 - m2 * x2 + y2 - y1) / (m1 - m2)
        // Burada, m1 ve m2 sırasıyla çizgilerin eğimleridir, x1 ve x2 çizgilerin x koordinatlarıdır,
        // y1 ve y2 çizgilerin y koordinatlarıdır. Bu formül, iki çizginin kesişim noktasının x koordinatını hesaplamak için kullanılır.
        double x = (m1 * this->getP1().getX() - m2 * nokta.getX() + nokta.getY() - this->getP1().getY()) / (m1 - m2);

        // Çizginin denklemini kullanarak kesişim noktasının y koordinatını hesapla
        // Bu adımda, çizginin denklemi (y = mx + b) kullanılarak, x koordinatı bilinen kesişim noktasının
        // y koordinatını hesaplıyoruz. Denklem: y = m1 * (x - x1) + y1
        // Burada, m1 çizginin eğimidir, x1 çizginin x koordinatıdır ve y1 çizginin y koordinatıdır.
        // Bu formül, x koordinatı bilinen kesişim noktasının y koordinatını hesaplamak için kullanılır.
        double y = m1 * (x - this->getP1().getX()) + this->getP1().getY();

        return Nokta(x, y);
    }


    Nokta ortaNokta() const {
        double x = (this->getP1().getX() + this->getP2().getX()) / 2.0;
        double y = (this->getP1().getY() + this->getP2().getY()) / 2.0;
        return Nokta(x, y);
    }

    std::string toString() const {
        return this->getP1().toString() + " - " + this->getP2().toString();
    }


    void yazdir() const {
        std::cout << this->toString() << std::endl;
    }
};

class Daire {
private:
    Nokta merkez;
    double yaricap;
public:
    // Daire sınıfının yapıcı metodları
    Daire(const Nokta& merkez, double yaricap) {
        this->setMerkez(merkez);
        this->setYaricap(yaricap);
    }

    Daire(const Daire& daire) {
        this->setMerkez(daire.merkez);
        this->setYaricap(daire.yaricap);
    }

    Daire(const Daire& daire, double x) {
        /*
            X'in pozitif verilmemesi durumu kontrol edilir.
            Eğer negatif verilmişse, pozitif yapılır.

            Burada ikinci bir ihtimal olarak hata fırlatılabilir.
            Pdf dosyasında net bir belirtme olmadığı için, bu şekilde bıraktım.
        */
        if (x < 0) {
            x = (-1.0) * x;
            //throw std::invalid_argument("X negatif olamaz.");
        }

        this->setMerkez(daire.merkez);
        this->setYaricap(daire.yaricap * x);
    }

    // Daire sınıfının get ve set metodları
    Nokta getMerkez() const {
        return merkez;
    }

    double getYaricap() const {
        return yaricap;
    }

    void setMerkez(const Nokta& merkez) {
        this->merkez = merkez;
    }

    void setYaricap(double yaricap) {
        this->yaricap = yaricap;
    }

    void setMerkez(double x, double y) {
        this->merkez.set(x, y);
    }

    double alan() const {
        // M_PI, cmath kütüphanesinde tanımlıdır.
        // Pi * r^2
        return M_PI * pow(this->getYaricap(), 2);
    }

    double cevre() const {
        // M_PI, cmath kütüphanesinde tanımlıdır.
        // 2 * Pi * r
        return 2 * M_PI * this->getYaricap();
    }

    int kesisim(const Daire& daire) const {

        // iki nokta arası mesafe formülü.
        double merkezlerArasiMesafe = sqrt(pow(this->getMerkez().getX() - daire.getMerkez().getX(), 2) + pow(this->getMerkez().getY() - daire.getMerkez().getY(), 2));

        // Eğer merkezler arası mesafe + diğer dairenin yarıçapı, bu dairenin yarıçapından küçükse daire içinde demektir.
        if (merkezlerArasiMesafe + daire.getYaricap() < this->getYaricap()) {
            return 0;
        }

        // Eğer içiçe değil fakat merkezler arası mesafe de iki yarıçapın toplam mesafesinden küçükse daireler birbiriyle örtüşüyordur.
        else if (merkezlerArasiMesafe < this->getYaricap() + daire.getYaricap()) {
            return 1;
        }

        // Daireler içiçe değil ve birbirlerini kesmiyorlarsa, hiç kesişim yoktur.
        else {
            return 2;
        }

    }

    std::string toString() const {
        return this->getMerkez().toString() + " - " + std::to_string(this->getYaricap());
    }

    void yazdir() const {
        std::cout << this->toString() << std::endl;
    }

};

class Ucgen {
private:
    Nokta nokta1;
    Nokta nokta2;
    Nokta nokta3;
public:
    // Ucgen sınıfının yapıcı metodu
    Ucgen(const Nokta& nokta1, const Nokta& nokta2, const Nokta& nokta3) {
        this->setNokta1(nokta1);
        this->setNokta2(nokta2);
        this->setNokta3(nokta3);
    }

    // Ucgen sınıfının get ve set metodları
    Nokta getNokta1() const {
        return nokta1;
    }

    Nokta getNokta2() const {
        return nokta2;
    }

    Nokta getNokta3() const {
        return nokta3;
    }

    void setNokta1(const Nokta& nokta1) {
        this->nokta1 = nokta1;
    }

    void setNokta2(const Nokta& nokta2) {
        this->nokta2 = nokta2;
    }

    void setNokta3(const Nokta& nokta3) {
        this->nokta3 = nokta3;
    }

    void setNokta1(double x, double y) {
        this->nokta1.set(x, y);
    }

    void setNokta2(double x, double y) {
        this->nokta2.set(x, y);
    }

    void setNokta3(double x, double y) {
        this->nokta3.set(x, y);
    }

    // Ucgen sınıfının diğer metodları
    std::string toString() const {
        return "üçgen: " + this->getNokta1().toString() + " - " + this->getNokta2().toString() + " - " + this->getNokta3().toString();
    }

    double alan() const {

        // Her kenarın uzunluğu hesaplanır.
        double a = DogruParcasi(nokta1, nokta2).uzunluk();
        double b = DogruParcasi(nokta1, nokta3).uzunluk();
        double c = DogruParcasi(nokta2, nokta3).uzunluk();

        // Çemberin yarı çevresi hesaplanır.
        double yari_cevre = (a + b + c) / 2.0;

        /*
            Alan = √(s(s-a)(s-b)(s-c))
        */
        return sqrt(yari_cevre * (yari_cevre - a) * (yari_cevre - b) * (yari_cevre - c));
    }

    double cevre() const {
        // Her kenarın uzunluğu hesaplanır.
        double a = DogruParcasi(nokta1, nokta2).uzunluk();
        double b = DogruParcasi(nokta1, nokta3).uzunluk();
        double c = DogruParcasi(nokta2, nokta3).uzunluk();

        return a + b + c;
    }

    double* acilar() const {
        double a = DogruParcasi(nokta1, nokta2).uzunluk();
        double b = DogruParcasi(nokta1, nokta3).uzunluk();
        double c = DogruParcasi(nokta2, nokta3).uzunluk();

        // Kosinüs teoremi ile açılar hesaplanır.
        double A_radyan = acos((b * b + c * c - a * a) / (2 * b * c));
        double B_radyan = acos((c * c + a * a - b * b) / (2 * c * a));
        double C_radyan = acos((a * a + b * b - c * c) / (2 * a * b));

        // Açılar radyandan dereceye çevrilir.
        double A_derece = A_radyan * 180 / M_PI;
        double B_derece = B_radyan * 180 / M_PI;
        double C_derece = C_radyan * 180 / M_PI;

        // Açılar diziye atılır.
        double* acilar = new double[3];
        acilar[0] = A_derece;
        acilar[1] = B_derece;
        acilar[2] = C_derece;

        return acilar;
    }


};




int main() {
    setlocale(LC_ALL, "Turkish");
    //Nokta
    cout << endl << "NOKTA SINIFI İÇİN TEST ÇIKTILARI:" << endl;
    Nokta n1;
    Nokta n2(5);
    Nokta n3(3, 4);
    Nokta n4(n3);
    Nokta n5(n3, 1, -1);

    cout << "Oluşturulan 5 noktanın x ve y değerleri:" << endl;
    n1.yazdir();
    n2.yazdir();
    n3.yazdir();
    n4.yazdir();
    n5.yazdir();

    cout << "1. ve 2. noktaların güncel x ve y değerleri:" << endl;
    n1.setX(10);
    n1.yazdir();
    n2.set(25, 30);
    n2.yazdir();

    //Dogru Parcasi
    cout << endl << "DOGRUPARCASI SINIFI İÇİN TEST SONUÇLARI:" << endl;
    Nokta n11;
    Nokta n21(3, 4);
    DogruParcasi dp(n11, n21);
    DogruParcasi dp2(dp);
    DogruParcasi dp3(n21, 10, 45);

    cout << "Oluşturulan 3 doğru parçasının başlangıç ve bitiş noktaları:" << endl;
    dp.yazdir();
    dp2.yazdir();
    dp3.yazdir();

    cout << "2. doğru parçasının başlangıç ve bitiş noktaları:" << endl;
    dp2.setP1(Nokta());
    dp2.yazdir();

    cout << "1. doğru parçası için uzunluk değeri: " << dp.uzunluk() << endl;
    cout << "1. doğru parçası içib orta nokta: " << dp.ortaNokta().toString() << endl;

    //Daire
    cout << endl << "DAIRE SINIFI İÇİN TEST SONUÇLARI:" << endl;
    Nokta merkez1(0, 0);
    Daire d1(merkez1, 5);
    Daire d2(d1);
    Daire d3(d2, 3);

    cout << "Daire 1: ";
    d1.yazdir();
    cout << "Alan: " << d1.alan() << ", Çevre: " << d1.cevre() << endl;

    cout << "Daire 2: ";
    d2.yazdir();
    cout << "Alan: " << d2.alan() << ", Çevre: " << d2.cevre() << endl;

    cout << "Daire 3: ";
    d3.yazdir();
    cout << "Alan: " << d3.alan() << ", Çevre: " << d3.cevre() << endl;

    cout << "Daire 1 ve Daire 2 Kesişim Durumu: " << d1.kesisim(d2) << endl;
    cout << "Daire 1 ve Daire 3 Kesişim Durumu: " << d1.kesisim(d3) << endl;

    //Ucgen
    cout << endl << "UCGEN SINIFI İÇİN TEST SONUÇLARI:" << endl;
    Ucgen ucgen(Nokta(0, 0), Nokta(4, 0), Nokta(0, 3));

    cout << ucgen.toString() << endl;
    cout << "Alan: " << ucgen.alan() << endl;
    cout << "Çevre: " << ucgen.cevre() << endl;

    double* acilar = ucgen.acilar();
    cout << "Açılar: " << acilar[0] << ", " << acilar[1] << ", " << acilar[2] << endl;


    return 0;
}