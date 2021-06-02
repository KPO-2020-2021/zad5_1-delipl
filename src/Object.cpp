#include "config.hpp"
#include "Object.hpp"
#include <fstream>

Object::Object(const std::string name, const Vector3 &centerPosition,
               const Vector3 &scale)
    : Transform(), id{Object::HMO} {
    this->lenPointsPack = 0;
    this->scale = scale;

    std::ifstream readFile(DATA_FOLDER + name);
    if(readFile.good())
        readFile >> *this;
    else{
        system("pwd");
        throw std::logic_error("Cannot read object file! " + std::string(DATA_FOLDER) + name);
    }
    readFile.close();

    this->originPoints = std::vector<Vector3>(this->actualPoints.size(), Vector3());
    this->originPoints = this->actualPoints;

    ++Object::HMO;
    this->name = std::to_string(this->id) + "_" + name;
    this->Translate(centerPosition);
}

Object::Object(const Object &obj): id{Object::HMO} {
    this->actualPoints.clear();
    this->originPoints.clear();
    this->actualPoints = std::vector<Vector3>(obj.CountPoints(), Vector3());
    this->originPoints = std::vector<Vector3>(obj.CountPoints(), Vector3());

    this->name = obj.Name();
    this->lenPointsPack = obj.LengthOfPointPack();
    this->rotation = obj.rotation;
    this->scale = obj.scale;
    this->position = obj.position;

    this->originPoints = obj.OriginPoints();
    for(std::size_t i = 0; i < obj.CountPoints(); ++i){
        this->actualPoints[i] = obj[i];
    }

    this->originPoints = this->actualPoints;
    ++Object::HMO;
}
Object::~Object() {
    this->actualPoints.clear();
    --Object::HMO;
}

Vector3 & Object::operator[](const std::size_t &index) { 
    if(index >= this->actualPoints.size())
        throw std::overflow_error("Vector overflow!");
    return this->actualPoints[index];
}   
Vector3 Object::operator[](const std::size_t &index) const{ 
    if(index >= this->actualPoints.size())
        throw std::overflow_error("Vector overflow!");
    return this->actualPoints[index];
}

void Object::Save(){
    std::ofstream tmpFile(TMP_FOLDER + this->Name());
    if(tmpFile)
        tmpFile << *this;
    tmpFile.close();
}

void Object::Translate(const Vector3 &v) {
    this->position += v;
}

void Object::Rotate(const double &angle, const Vector3 &v) {
    if(v != VectorX && v != VectorY && v != VectorZ)
        throw std::logic_error("Cannot rotate");
    this->eulerAngles += v * angle;
}

std::vector<Vector3> Object::OriginPoints() const{
    return this->originPoints;
}

void Object::Update(){
    this->actualPoints = this->originPoints;
    MatrixTransform M(this->position, this->eulerAngles, this->scale);

    for (auto &x : this->actualPoints){
        Vector4 y({x[0], x[1], x[2], 1});
        y = M * y;
        x = Vector3({y[0], y[1], y[2]});
    }

    this->Save();
}

std::istream &operator>>(std::istream &strm, Object &object){
    object.actualPoints.clear();
    std::size_t onePack = 0;
    while (!strm.eof()){
        if (strm.peek() == '#') {
            strm.get();
        } 
        else if (strm.peek() == '\n') {
            strm.get();
            if (strm.peek() == '\n'){
                object.lenPointsPack = onePack;
            }
        }

        Vector3 x;
        try{
            strm >> x;
        }
        catch(std::logic_error &e){
            strm.clear();
            return strm;
            
        }

        if(!strm)
            throw std::logic_error("Cannot read Object!");

        object.actualPoints.push_back(x);

        if(object.lenPointsPack == 0)
            ++onePack;
    }
    return strm;
}


std::ostream &operator<<(std::ostream &strm, const Object &object){
    std::size_t k = 1;
    for(std::size_t i = 0; i < object.CountPoints(); ++i){
        strm << object[i] << std::endl;
        if(k == object.LengthOfPointPack()) {
            strm << "#\n\n";
            k = 0;
        }
        if(!strm)
            throw std::logic_error("Cannot read Object!");
        ++k;
    }
    return strm;
}