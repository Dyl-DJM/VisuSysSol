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
#include "tools.hpp"

class Camera
{
public:
    /**
     * @brief Constructor.
     *
     * @param distToCenter A distance on z axis from the center of the scene.
     * @param angle A degree value representing the camera rotation around the x-axis.
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

    /**
     * @brief Returns the camera view matrix.
     */
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

    /**
     * @brief Makes a basic view Matrix computation.
     *
     * Computes the camera view matrix thanks to distance and angles information.
     */
    void initialConfig();

    /**
     * @brief Checks if the camera is currently in the focused mode.
     *
     * @return True if the camera is currently in the focused mode and false otherwise.
     */
    bool isFocusedPov();

    /**
     * @brief Sets the camera in the focused mode.
     */
    void setFocusedPov();

    /**
     * @brief Sets the camera in the default mode.
     */
    void setInitialPov();

    /**
     * @brief Checks if the camera is currently in the default mode.
     *
     * @return True if the camera is currently in the default mode and false otherwise.
     */
    bool isInitialPov();

    /**
     * @brief Checks if the camera is currently in the profile mode.
     *
     * @return True if the camera is currently in the profile mode and false otherwise.
     */
    bool isProfilePov();

    /**
     * @brief Sets the camera in the profile mode.
     */
    void setProfilePov();

    static const float initialDistance;
    static const float initialAngleX;
    static const float initialAngleY;

private:
    enum POV_STATE
    {
        GENERAL, // 3/4 view mode
        FOCUSED, // Planet focused mode
        PROFILE  // Sun profile view
    };

    POV_STATE _pov = GENERAL;
    float m_fDistance;  // Distance from the center of the scene
    float m_fAngleX;    // Rotation angle on the X axis
    float m_fAngleY;    // Rotation angle on the Y axis
    glm::vec3 position; // Position of the camera
    glm::mat4 view_matrix;
};

inline const float Camera::initialDistance = 18;
inline const float Camera::initialAngleX = fractionToDegrees(3, 4);
inline const float Camera::initialAngleY = 0;