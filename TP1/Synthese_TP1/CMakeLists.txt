# CMakeList.txt : projet CMake pour Synthese_TP1, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)


project ("Synthese_TP1")

# Current directory is Synthese_TP1
set(glm_DIR ../../libraries/glm-master/glm-master/cmake/glm)
find_package( glm REQUIRED )

# Ajoutez une source à l'exécutable de ce projet.
add_executable (Synthese_TP1 "Synthese_TP1.cpp" "Synthese_TP1.h" "Parachutist.h" "Parachutist.cpp")

target_link_libraries(${PROJECT_NAME} glm::glm)
# TODO: Ajoutez des tests et installez des cibles si nécessaire.

