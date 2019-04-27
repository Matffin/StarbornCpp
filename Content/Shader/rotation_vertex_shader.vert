#extension GL_EXT_gpu_shader4 : enable

uniform float dtAsSeconds;
uniform float ttAsSeconds;
uniform float simTime;
uniform float random;

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

vec4 rotate(vec4 v, vec3 axis, float angle);
vec4 rotate(vec4 v, vec3 axis, float angle) {
    mat4 m = rotationMatrix(axis, angle);
    vec4 r = m * v;
    return r;
}

vec4 transform(vec4 v, vec4 add);
vec4 transform(vec4 v, vec4 add){
    return v+add;
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
//    float s = sin(angle);
//    float c = cos(angle);
//    mat2 m = mat2(c, -s, s, c);
    // transform the vertex position

    vec4 center = vec4(768.3f,768.3f,0,1);

    float randomNr = gl_VertexID/100;
    vec2 randomSeed = vec2(randomNr,random);
    float randomSpeed = rand(randomSeed)-0.5;
    float angle = randomSpeed * gl_Vertex.length * simTime;

    vec3 rotationAxis = vec3(0.0,0.0,1);

    float test = dtAsSeconds;

    float sinValue = randomSpeed * simTime;
    float sinWave = sin(sinValue-gl_VertexID/10000) * (1-transform(gl_Vertex.length,center));
    vec4 transformPosition = vec4(0,sinWave,0,1);

    gl_Position = gl_ModelViewProjectionMatrix  *
    transform(rotate(transform(gl_Vertex,transformPosition),rotationAxis,angle),center);

    // transform the texture coordinates
    gl_TexCoord[0] =  gl_TextureMatrix[0]*gl_MultiTexCoord0;//

    // forward the vertex color
    gl_FrontColor = gl_Color;
}

