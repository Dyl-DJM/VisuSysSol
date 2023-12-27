/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Module defining the Camera class and it's methods =
=													 =
======================================================
*/

#pragma once

#include <glimac/common.hpp>


class Camera{
    public:

        /**
         * @brief Constructor
        */
        Camera();

        /**
         * @brief Move the camera forward.
         * 
         * @param delta Number of unit to move forward (or backward if negative) from.
        */
        void moveFront(float delta);

        /**
         * @brief Rotate the camera horizontally.
         * 
         * @param degrees Angle in degree to rotate horizontally for. Positive degree will rotate left, negate will rotate right.
        */
        void rotateLeft(float degrees);

        /**
         * @brief Rotate the camera vertically.
         * 
         * @param degree Angle in degree to rotate vertically for. Positive degree will rotate up, negate will rotate down.
        */
        void rotateUp(float degrees);


        glm::mat4 getViewMatrix() const;

        /**
         * @brief Update the camera's position depending on the target planet's position
         * 
         * @param targetPosition the position of the targeted planet
        */
        void update_position(glm::vec4 targetPosition);

        /**
         * @brief Set a distance for the camera
         * 
         * @param distance The distance to set
        */
       void set_distance(float distance);

    private:
        float m_fDistance;
        float m_fAngleX;       // Rotation angle on the X axis
        float m_fAngleY;       // Rotation angle on the Y axis
        glm::vec3 position;    // Position of the camera
        glm::mat4 view_matrix;  

};