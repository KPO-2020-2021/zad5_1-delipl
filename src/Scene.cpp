#include "Scene.hpp"

Scene::Scene(){
    this->UsunWszystkieNazwyPlikow();
    this->_Xmax =  10 * WINDOW_SCALE;
    this->_Xmin = -10 * WINDOW_SCALE;
    this->_Ymax =  10  * WINDOW_SCALE;
    this->_Ymin = -10  * WINDOW_SCALE;
    this->_Zmax =  10  * WINDOW_SCALE;
    this->_Zmin =  -10 * WINDOW_SCALE;

    // this->UstawSkaleXZ(10*WINDOW_SCALE, -10*WINDOW_SCALE);
    // this->UstawSkaleY(10*WINDOW_SCALE);

    this->ZmienTrybRys(PzG::TR_3D);
    this->Inicjalizuj();

    this->activeObjects = std::vector<Object>();
}

Scene::~Scene(){
    system("rm ./tmp/*");
    system("killall gnuplot");
    this->activeObjects.clear();
}

void Scene::AddObject(const Object &obj){
    this->activeObjects.push_back(obj);
    this->DodajNazwePliku(std::string(TMP_FOLDER + obj.Name()).c_str());
}

Object &Scene::operator[](const std::size_t &i){
    if(i >= this->activeObjects.size())
        throw std::overflow_error("There is no more objects");
    return this->activeObjects[i];
}

Object Scene::operator[](const std::size_t &i) const{
    if(i >= this->activeObjects.size())
        throw std::overflow_error("There is no more objects");
    return this->activeObjects[i];
}
        
void Scene::Update(){
    for(auto &obj : this->activeObjects){
        obj.Update();
    }
    
    this->Rysuj();
}
