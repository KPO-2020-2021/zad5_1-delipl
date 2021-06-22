/**
 * @file Scene.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
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

/**
 * @brief English name for PzG::LaczeDoGNUPlota
 */
typedef PzG::LaczeDoGNUPlota GNUPlotApi;


/**
 * @brief class has Objects and can manipulate and display them on screen
 */
class Scene {
    /**
     * @brief std::vector of  objects on Scene
     */
    std::vector<std::shared_ptr<SceneObject>> activeObjects;

  public:
    /**
     * @brief Api for GNUPlot to display and animate SceneObjects
     */
    inline static GNUPlotApi api = GNUPlotApi();

   
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

    /**
     * @brief Draw SceneObject without saving into activeObjects
     * @param obj SceneObject to draw.
     */
    static void Draw(SceneObject const *obj);

    static void AddToDrawable(SceneObject const *obj);

    static void Clear();
};
#endif  // __SCENE_HPP__