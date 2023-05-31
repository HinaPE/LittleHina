cmake_minimum_required(VERSION 3.24)
project(LittleHina VERSION 2.0.0 DESCRIPTION "A Little Little Little Little Little HinaPE" LANGUAGES CXX)

set(SRC
        platform.h
        platform.cpp

        deps/imgui/imgui.h
        deps/imgui/imconfig.h
        deps/imgui/imgui_internal.h
        deps/imgui/imstb_rectpack.h
        deps/imgui/imstb_textedit.h
        deps/imgui/imstb_truetype.h
        deps/imgui/implot.h
        deps/imgui/implot_internal.h
        deps/imgui/GraphEditor.h
        deps/imgui/ImCurveEdit.h
        deps/imgui/ImGradient.h
        deps/imgui/ImGuizmo.h
        deps/imgui/ImSequencer.h
        deps/imgui/ImZoomSlider.h
        deps/imgui/backends/imgui_impl_opengl3.h
        deps/imgui/backends/imgui_impl_glfw.h

        deps/imgui/imgui.cpp
        deps/imgui/imgui_draw.cpp
        deps/imgui/imgui_widgets.cpp
        deps/imgui/imgui_tables.cpp
        deps/imgui/implot.cpp
        deps/imgui/implot_items.cpp
        deps/imgui/GraphEditor.cpp
        deps/imgui/ImCurveEdit.cpp
        deps/imgui/ImGradient.cpp
        deps/imgui/ImGuizmo.cpp
        deps/imgui/ImSequencer.cpp
        deps/imgui/backends/imgui_impl_opengl3.cpp
        deps/imgui/backends/imgui_impl_glfw.cpp

        deps/imterm/misc.hpp
        deps/imterm/terminal.hpp
        deps/imterm/terminal.tpp
        deps/imterm/terminal_helpers.hpp
        deps/imterm/utils.hpp
        )
if (NOT TARGET glad)
    add_subdirectory(deps/glad)
    target_include_directories(glad PUBLIC deps)
endif ()
if (NOT TARGET glfw)
    add_subdirectory(deps/glfw3)
endif ()

add_library(LittleHina STATIC)
target_sources(LittleHina
        PUBLIC
        ${SRC}
        )

set_target_properties(LittleHina PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_include_directories(LittleHina PUBLIC deps deps/glfw3/include deps/imgui deps/imterm)
target_link_libraries(LittleHina PUBLIC glad)
target_link_libraries(LittleHina PUBLIC glfw)

# EXE START HERE
add_executable(LittleHina_APP
        main.cpp
        )
set_target_properties(LittleHina_APP PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS ON)
target_link_libraries(LittleHina_APP PUBLIC LittleHina)
