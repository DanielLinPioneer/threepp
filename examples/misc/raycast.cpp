
#include "threepp/threepp.hpp"

#include "threepp/core/Raycaster.hpp"

using namespace threepp;

int main() {

    Canvas canvas;
    GLRenderer renderer(canvas);
    renderer.checkShaderErrors = true;
    renderer.setClearColor(Color::aliceblue);

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->layers.enableAll();
    camera->position.z = 5;

    OrbitControls controls(camera, canvas);

    const auto boxGeometry = BoxGeometry::create();
    const auto boxMaterial = MeshBasicMaterial::create();
    boxMaterial->color = Color::green;
    auto box = Mesh::create(boxGeometry, boxMaterial);
    scene->add(box);

    const auto planeGeometry = PlaneGeometry::create(5, 5);
    const auto planeMaterial = MeshBasicMaterial::create();
    planeMaterial->color = Color::yellow;
    planeMaterial->side = DoubleSide;
    auto plane = Mesh::create(planeGeometry, planeMaterial);
    plane->position.z = -2;
    scene->add(plane);

    float sphereRadius = 0.1f;
    const auto sphereGeometry = SphereGeometry::create(sphereRadius);
    const auto sphereMaterial = MeshBasicMaterial::create();
    sphereMaterial->color = Color::black;
    auto sphere = Mesh::create(sphereGeometry, sphereMaterial);
    sphere->visible = false;
    sphere->layers.set(1);
    scene->add(sphere);

    auto grid = GridHelper::create();
    grid->position.y = -4;
    scene->add(grid);

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.getAspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    Vector2 mouse{-Infinity<float>, -Infinity<float>};
    MouseMoveListener l([&](Vector2 pos) {
        // calculate mouse position in normalized device coordinates
        // (-1 to +1) for both components

        auto size = canvas.getSize();
        mouse.x = (pos.x / static_cast<float>(size.width)) * 2 - 1;
        mouse.y = -(pos.y / static_cast<float>(size.height)) * 2 + 1;
    });
    canvas.addMouseListener(&l);

    Raycaster raycaster;
    raycaster.params.lineThreshold = 0.1f;
    canvas.animate([&](float dt) {
        raycaster.setFromCamera(mouse, camera);

        sphere->visible = false;
        auto intersects = raycaster.intersectObjects(scene->children);

        if (!intersects.empty()) {
            auto& intersect = intersects.front();

            sphere->position.copy(intersect.point);
            if (intersect.face) {
                sphere->position += (intersect.face.value().normal * sphereRadius);
            }
            sphere->visible = true;
        }

        renderer.render(scene, camera);
    });
}
