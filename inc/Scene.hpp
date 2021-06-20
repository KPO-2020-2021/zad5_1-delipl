/**
 * @file Scene.hpp
 * @author your name (you@domain.com)
 * @brief Describes scene module
 * @version 0.1
 * @date 2021-06-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __SCENE_HPP__
#define __SCENE_HPP__
#include <vector>

#include "config.hpp"
#include "Drone.hpp"
#include "GnuPlotApi.hpp"

typedef PzG::LaczeDoGNUPlota GNUPlotApi;
// class GNUPlotApi : public PzG::LaczeDoGNUPlota {
//   public:
//     GNUPlotApi() = default;
//     void UsunNazwePliku(const std::string &name) {
//          PzG::InfoPlikuDoRysowania toFind((std::string(TMP_FOLDER + name).c_str()),PzG::RodzajRysowania::RR_Ciagly,1);
//           this->_InfoPlikow.remove(toFind);
//     }

// };

/**
 * @brief class has Objects and can manipulate and display them on screen
 */
class Scene {
    /**
     * @brief std::vector of  objects on Scene
     */
    std::vector<std::shared_ptr<SceneObject>> activeObjects;



    // 

  public:
    /**
     * 
     * @brief Api for GNUPlot to display and animate SceneObjects
     */
    inline static GNUPlotApi api = GNUPlotApi();

    /**
          *  
      * @brief Draw SceneObject without saving into activeObjects
      * @param obj SceneObject to draw.
      */
    inline static void Draw(SceneObject const *obj, const bool &show = true) {
        api.DodajNazwePliku((std::string(TMP_FOLDER + obj->Name()).c_str()));
        api.ZmienTrybRys(PzG::TR_3D);
        if(show)
          api.Rysuj();
        api.UsunOstatniaNazwe();
    }

    inline static void AddToDrawable(SceneObject const *obj, const bool &show = true) {
        api.DodajNazwePliku((std::string(TMP_FOLDER + obj->Name()).c_str()));
        api.ZmienTrybRys(PzG::TR_3D);
        if(show)
          api.Rysuj();
    }

     inline static void Clear(){
         api.UsunWszystkieNazwyPlikow();
     }
    /**
         * @brief Construct a new Scene object and creates new GnuPlot window
         */
     Scene();

     /**
         * @brief Destroy the Scene object and all objects on Scene and kilall Gnuplot
         */
     ~Scene();

     /**
         * @brief Links existing Object to Scene
         * @param obj Object
         */
     void Add(const std::shared_ptr<SceneObject> &obj);

     void Remove(const std::size_t &ID);

     /**
         * @brief Apply all moving functions to Objects
         */
     void Update();

     std::size_t CountObjects() const;

     /**
         * @brief Access funtion to write objects
         * @param i ID of SceneObject
         * @return Object
         */
     std::shared_ptr<SceneObject> &operator[](const std::size_t &i);

     /**
         * @brief Access funtion to read objects
         * @param i ID of SceneObject
         * @return Object
         */
     std::shared_ptr<SceneObject> operator[](const std::size_t &i) const;
};
#endif  // __SCENE_HPP__