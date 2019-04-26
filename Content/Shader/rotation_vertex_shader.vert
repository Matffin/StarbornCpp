uniform float angle;
//
mat4 rotationMatrix(vec3 axis, float angle);
mat4 rotationMatrix(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
    oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
    oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
    0.0,                                0.0,                                0.0,                                1.0);
}

vec3 rotate(vec3 v, vec3 axis, float angle);
vec3 rotate(vec3 v, vec3 axis, float angle) {
    mat4 m = rotationMatrix(axis, angle);
    return (m * vec4(v, 1.0)).xyz;
}


void main()
{
//    float s = sin(angle);
//    float c = cos(angle);
//    mat2 m = mat2(c, -s, s, c);
    // transform the vertex position
    gl_Position = rotationMatrix(vec3(0.0,0.0,1.0),angle) * gl_ModelViewProjectionMatrix * gl_Vertex;

    // transform the texture coordinates
    gl_TexCoord[0] =  gl_TextureMatrix[0]*gl_MultiTexCoord0;//

    // forward the vertex color
    gl_FrontColor = gl_Color;
}

