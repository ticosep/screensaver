#version 400
layout(location = 0) in vec4 vPosition;
out vec4 v2fcolor;

uniform mat4 model;


void main ()
{
    gl_Position = model * vPosition;
    // We could infer the depth of the model
    float gray = (gl_Position.z + 1) * 0.5;

    // Change the R escale to pink
    v2fcolor = vec4(gray + 0.5, gray, gray, 1);

}
