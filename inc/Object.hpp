#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Matrixes.hpp"
/**
 * @file
 * Describes Transform Class and Object Class
 */

/**
 * @brief Collects position, angles and scale of whole object. 
 */
struct Transform{
    public:
        /**
         * @brief Pinned Transform
         */
        std::shared_ptr<Transform> pinned;

        /**
         * @brief Center position
         */
        Vector3 position;

        /**
         * @brief Rotation Matrix
         */
        MatrixRot rotation;

        /**
         * @brief Euler angles in 3 axis
         */
        Vector3 eulerAngles;

        /**
         * @brief Scale as a unit matrix
         */
        MatrixRot scale;

        /**
         * @brief Construct a new Transform object
         */
        Transform(){
            this->pinned = nullptr;
            this->position    = Vector3();
            this->rotation    = MatrixRot();
            this->scale       = MatrixRot();
            this->eulerAngles = Vector3();
        }
};
/**
 * @brief Object Class, base class for printed activeObjects on screen
 */
class Object: public Transform{
    private:
        /**
         * @brief id of object
         */
        const std::size_t id;

        /**
         * @brief Name of Object
         */
        std::string name;

        /**
         * @brief List of actualPoints of Object
         */
        std::vector<Vector3> actualPoints;


        /**
         * @brief List of origin points
         */
        std::vector<Vector3> originPoints;

        /**
         * @brief How many points should be in one pack. Packs are separated with new line.
         */
        std::size_t lenPointsPack;

        /**
         * @brief Save actualPoints into file name
         */
        void Save();

        /**
         * @brief Number of Objects
         */
        inline static std::size_t HMO = 0;

       public:
        /**
         * @brief Construct a new Object object
         * @param name of file in dat/ folder and of Object
         * @param centerPosition center position of object default {0, 0, 0}
         * @param scale scale of object default {1, 1, 1}
         */
        Object(const std::string name, const Vector3 &centerPosition = Vector3(),  const Vector3 &scale = {1, 1, 1});

        /**
         * @brief Construct a new Object object
         * @param obj copied Object
         */
        Object(const Object &obj);

        /**
         * @brief Destroy the Object object 
         */
        virtual ~Object();

        /**
         * @brief Acces function for name of Object
         * @return std::string name of Object
         */
        std::string Name() const { return this->name; }

        /**
         * @brief Counts number of actualPoints
         * @return std::size_t quantity of actualPoints
         */
        std::size_t CountPoints() const {return this->actualPoints.size();}

        /**
         * @brief Acces function for reading every actualPoints
         * @param index of point in \a actualPoints
         * @return Vector3 point
         */
        Vector3 operator[](const std::size_t &index) const;

        /**
         * @brief Acces function for writing every actualPoints
         * @param index of point in \a actualPoints
         * @return Vector3 point
         */
        Vector3 &operator[](const std::size_t &index);

        /**
         * @brief Translates every point from \a actualPoints and \a transform of Object
         * @param v translate Vector3
         */
        virtual void Translate(const Vector3 &v = Vector3());

        /**
         * @brief Rotates every point from \a actualPoints and \a transform of Object
         * @param angle angle of rotation
         * @param times how many rotate Object
         * @param v Vector3 of axis rotation
         */
        virtual void Rotate(const double &angle, const Vector3 &v);

        /**
         * @brief Read origin points
         * @return std::vector<Vector3> 
         */
        std::vector<Vector3> OriginPoints() const;

        /**
         * @brief Access function to id of Object
         * @return std::size_t 
         */
        std::size_t SeflID() const { return this->id;}

        /**
         * @brief Acces function for lenPointsPack
         */
        std::size_t LengthOfPointPack() const { return this->lenPointsPack; }

        /**
         * @brief Update points. Make rotaion and translation
         */
        virtual void Update();

        /**
         * @brief Acces function to HMO
         * @return std::size_t const number of objects
         */
        inline static std::size_t HowManyObjects() { return Object::HMO; }

        /**
         * @brief reading temporary file which is used for printing in GnuPlot
         * @return Object read 
         */
        Object ReadTemporaryFile() const;

        /**
         * @brief Writing all \a actualPoints to \a Object 
         * @param strm input stream
         * @param object written \a Object
         * @return std::istream& 
         */
        friend std::istream &operator>>(std::istream &strm, Object &object);

        /**
         * @brief Printing all \a actualPoints from \a Object 
         * @param strm output stream
         * @param object printed \a Object
         * @return std::ostream& 
         */
        friend std::ostream &operator<<(std::ostream &strm, const Object &object);
};



#endif // __OBJECT_HPP__