#include "Scene.hpp"

Scene::Scene(){
    api.ZmienTrybRys(PzG::TR_3D);
    api.Inicjalizuj();

}

Scene::~Scene(){
    // system("pwd");
    system("killall gnuplot");
}

void Scene::Add(const std::shared_ptr<SceneObject> &obj) {
    // if(std::dynamic_pointer_cast<Drone>(obj) != nullptr){
    //     droneAnimations.push_back(Animate());
    // }
    this->activeObjects.push_back(obj);
    api.DodajNazwePliku(std::string(TMP_FOLDER + obj->Name()).c_str());
}

std::shared_ptr<SceneObject> &Scene::operator[](const std::size_t &i) {
    if(i >= this->activeObjects.size())
        throw std::overflow_error("There is no more objects");
    return this->activeObjects[i];
}

std::shared_ptr<SceneObject> Scene::operator[](const std::size_t &i) const {
    if(i >= this->activeObjects.size())
        throw std::overflow_error("There is no more objects");
    return this->activeObjects[i];
}

void Scene::Update(){

    for(auto &obj : this->activeObjects){
        obj->Update();
    }
    if(this->activeObjects.size() != 0)
        api.Rysuj();
    
}

std::size_t Scene::CountObjects() const{
    return this->activeObjects.size();
}

// void Scene::Animate() {
//     // std::size_t n = 0;
//     // for (auto &obj : this->activeObjects) {
//     //     auto localPtr = std::dynamic_pointer_cast<Drone>(obj);
//     //     if (localPtr != nullptr) {
//     //         ++n;
//     //         localPtr->Left();
//     //     }
//     // }
// }