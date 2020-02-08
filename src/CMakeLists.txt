
# include_directories( shapes )

add_subdirectory( shapes )

target_sources( city
    PRIVATE
        city.h
        shader.h
        shader.cpp
        setup.h
        setup.cpp
        texture.h
        texture.cpp
    PUBLIC
        city.cpp
    )

