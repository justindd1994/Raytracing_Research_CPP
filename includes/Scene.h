#ifndef SCENE_HPP
# define SCENE_HPP

#include <iostream>
#include <map>

#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Material.h"

class Scene
{
public:
    std::string title;
    HittableList world;

    Camera camera;

    Scene() {};
    Scene(std::string title);

    void addObject(shared_ptr<Hittable> hittableObject);
};

Scene::Scene(std::string title)
{
    this->title = title;
}

void Scene::addObject(shared_ptr<Hittable> hittableObject)
{
    this->world.add(hittableObject);
}

HittableList random_scene()
{
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = random_double();
            Point3 center(a + (0.9 * random_double()), 0.2, b + (0.9 * random_double()));

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

#endif