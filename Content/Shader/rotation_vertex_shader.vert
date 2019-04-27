#extension GL_EXT_gpu_shader4 : enable

uniform float dtAsSeconds;
uniform float ttAsSeconds;
uniform float simTime;
uniform float random;

attribute vec4 lastPos;

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

float gravity(vec3 p1_pos, vec3 p2_pos, float p1_mass, float p2_mass)
{
    float g = 9.81f;
    float distance = (p2_pos - p1_pos).length();
    return g * p1_mass * p1_mass / (distance*distance);
}

float angleCalculation(float time, float distance, float speed);
float angleCalculation(float time, float distance, float speed){

    if(distance<=1){
        distance = 1;
    }

    return ((speed * time)/(distance*distance));
}

vec4 sinCalculation(float time, float distance, float speed);
vec4 sinCalculation(float time, float distance, float speed){

    if(distance<=1){
        distance = 1;
    }

    float sinValue = speed * time;
    float sinWave = sin(sinValue-speed)/(distance*distance);
    return vec4(0,sinWave,0,1);
}

void main()
{
//    float s = sin(angle);
//    float c = cos(angle);
//    mat2 m = mat2(c, -s, s, c);
    // transform the vertex position

    vec4 center = vec4(768.3f,768.3f,0,1);

    vec3 rotationAxis = vec3(0.0,0.0,1);

    float randomNr = gl_VertexID/100;
    vec2 randomSeed = vec2(randomNr,random);
    float randomSpeed = (rand(randomSeed)-0.5)*0.1;


    float lastAngle = angleCalculation(simTime-0.1,gl_Vertex.length,randomSpeed);
    vec4 lastTransform = sinCalculation(simTime-0.1,gl_Vertex.length,randomSpeed);

    float lastDistance = transform(rotate(transform(gl_Vertex,lastTransform),rotationAxis,lastAngle),center);

  //  vec4 center = vec4(0,0,0,1);
   // simTime += iTimeDelta *simFactor;


    //vec3 rotationAxis = vec3(0.0,0.0,1);



    //float sinValue = randomSpeed * simTime;
    //float sinWave = sin(sinValue-gl_VertexID/10000) * (1-gl_Vertex.length) * 0;
    //vec4 transformPosition = vec4(0,sinWave,0,1);

    float angle = angleCalculation(simTime,lastDistance,randomSpeed);
    vec4 transformPosition = sinCalculation(simTime,lastDistance,randomSpeed);

    gl_Position = gl_ModelViewProjectionMatrix  *
    transform(rotate(transform(gl_Vertex,lastTransform),rotationAxis,lastAngle),center);

    //gl_Position = gl_ModelViewProjectionMatrix * transform(gl_Vertex,(center - gl_Vertex)*gravity(gl_Vertex,center,1,100000)*simTime);

    // transform the texture coordinates
    gl_TexCoord[0] =  gl_TextureMatrix[0]*gl_MultiTexCoord0;//

    // forward the vertex color
    gl_FrontColor = gl_Color;
}

