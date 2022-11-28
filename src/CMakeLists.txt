# Add files here to compile them together with CMake
set(CVP_SRC
    driver.cpp
    cvp.h
    cvp.cpp
    vector_ops.h
    vector_ops.cpp
    )

# Form full path to src files
PREPEND(CVP_SRC)

# Set variable to parent
set(CVP_SRC ${CVP_SRC} PARENT_SCOPE)
