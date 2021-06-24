#include "Scene.hpp"

Scene::Scene(){
    api.ZmienTrybRys(PzG::TR_3D);
    api.Inicjalizuj();
}

Scene::~Scene(){
    // system("pwd");
    // for (auto &obj : this->activeObjects)
    //     obj->~SceneObject();
    system("killall gnuplot  /usr/lib/gnuplot/gnuplot_qt");
}

void Scene::Add(const std::shared_ptr<SceneObject> &obj) {
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
    for (auto &obj : this->activeObjects)
        obj->Update();

    if(this->activeObjects.size() != 0)
        api.Rysuj();
}

std::size_t Scene::CountObjects() const{
    return this->activeObjects.size();
}

void Scene::Draw(SceneObject const *obj) {
    api.DodajNazwePliku((std::string(TMP_FOLDER + obj->Name()).c_str()));
    api.ZmienTrybRys(PzG::TR_3D);
    api.Rysuj();
    api.UsunNazwePliku(std::string(TMP_FOLDER + obj->Name()).c_str());
}

void Scene::AddToDrawable(SceneObject const *obj) {
    api.DodajNazwePliku((std::string(TMP_FOLDER + obj->Name()).c_str()));
    api.ZmienTrybRys(PzG::TR_3D);
}

void Scene::ClearGNUPlot() {
    api.UsunWszystkieNazwyPlikow();
}

std::shared_ptr<SceneObject> &Scene::SelectDrone(const std::size_t &index)
{
    std::size_t n = 0;
    for (auto &obj : this->activeObjects)
    {
        if (std::dynamic_pointer_cast<Drone>(obj) != nullptr)
        {
            ++n;
            if (n == index)
            {
                return obj;
            }
        }
    }
    throw std::logic_error("There is no drones");
    return activeObjects[0];
}