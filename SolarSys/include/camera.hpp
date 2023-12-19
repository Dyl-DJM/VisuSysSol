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
         * @brief Constructor of the class.
         *
         * @param rotation A float value that describes the rotation period of the
         *                 planet.
         * @param diameter A size for the planet.
         * @param position A position value regarding the sun position.
         * @param angle A value that represents the angle regarding the ellipse.
         ********************************************************************************/
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

    private:
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;

};