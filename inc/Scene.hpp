/**
 * @file Scene.hpp
 * @author Delicat Jakub (delicat.kuba@gmail.com)
 * @brief Describes Scene class
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
 * @brief Scene class menages printing SceneObjects on Scene by means of GNUPlotApi. 
 * It also menages every SceneObject on Scene and SceneObjects can be modified by Scene.
 */
class Scene {
    /**
     * @brief std::vector of pointers to SceneObject which are printed and collided on Scene.
     */
    std::vector<std::shared_ptr<SceneObject>> activeObjects;

  public:
    /**
     * @brief Api for GNUPlot to display and animate SceneObjects
     */
    inline static GNUPlotApi api = GNUPlotApi();

   
    /**
     * @brief Construct a new Scene object and creates new GnuPlot window.
     */
    Scene();

    /**
     * @brief Destroy the Scene object and all objects on Scene and kilall Gnuplot processes.
     */
    ~Scene();

    /**
     * @brief Adding SceneObject to Scene for printing and manipulating.
     * @param obj Object
     */
    void Add(const std::shared_ptr<SceneObject> &obj);

    void Remove(const std::size_t &ID);

    /**
     * @brief Apply all moving functions to Objects.
     */
    void Update();

    /**
     * @brief Counting existing SceneObjects on Scene.
     * @return std::size_t How many SceneObjects are on Scene.
     */
    std::size_t CountObjects() const;

    /**
     * @brief Access funtion to write SceneObject.
     * @param i ID of SceneObject.
     * @return std::shared_ptr<SceneObject> to SceneObject 
     */
    std::shared_ptr<SceneObject> &operator[](const std::size_t &i);

    /**
     * @brief Access funtion to read SceneObject.
     * @param i ID of SceneObject.
     * @return std::shared_ptr<SceneObject> to SceneObject 
     */
    std::shared_ptr<SceneObject> operator[](const std::size_t &i) const;

    /**
     * @brief Draw SceneObject one time without saving into activeObjects and make GNUPlot window if does not exist.
     * @param obj SceneObject to draw.
     */
    static void Draw(SceneObject const *obj);

    /**
     * @brief Add SceneObject to GNUPlot memory. It allows the @p obj be printed every time witout saving into activeObjects.
     * @param obj SceneObject to draw.
     */
    static void AddToDrawable(SceneObject const *obj);

    /**
     * @brief ClearGNUPlot all GNUPlot memory. It removes all SceneObjects from GNUPlot but not from Scene.
     */
    static void ClearGNUPlot();

    /**
     * @brief Select Drone which has index
     * @param index of drone
     * @return std::shared_ptr<Drone>& drone
     */
    std::shared_ptr<SceneObject> &SelectDrone(const std::size_t &index);
};
#endif  // __SCENE_HPP__