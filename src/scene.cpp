#include "sg/scene.hpp"
#include "sg/application-interface.hpp"

namespace sg
{

Scene::~Scene()
{
}

void Scene::pre_update(ApplicationInterface&)
{
}
void Scene::post_update(ApplicationInterface&)
{
}
void Scene::post_render(ApplicationInterface&)
{
}
void Scene::on_enter(ApplicationInterface&)
{
}
void Scene::on_leave(ApplicationInterface&)
{
}

}
