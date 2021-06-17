
class PakietDanych {
  public:
    int _DlugoscPakietu;
    static int _IloscWszystkichPakietow;

    PakietDanych() {}
};

int PakietDanych::_IloscWszystkichPakietow = 0;

int main() {
    const PakietDanych PkDan;

    PkDan._DlugoscPakietu = 100;
    PkDan._IloscWszystkichPakietow = 4;
}
