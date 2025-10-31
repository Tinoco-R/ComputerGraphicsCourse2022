#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

// Code implementation refers to this site:
// https://learnopengl.com/Lighting/Basic-Lighting
// The site fully covers each step of the fragmentation process (ambient, diffuse, // specular)

void main()
{
    // TODO: Replace with your code...

    // Ambient Lighting //
    // Arbitrarily set coefficient here
    float ambientCoefficient  = 0.1;
    vec3 ambient = ambientCoefficient * lightColor;

    // Diffuse Lighting //

    // Normalize Normal to get a unit vector that simplifies calculations
    vec3 norm = normalize(Normal);
    // Calculates light direction vector between LightPos and FragPos; normalizes       // as above
    vec3 lightDir = normalize(lightPos - FragPos);

    // Energy received is a value from 0 (norm perp to lightDir) to 1 (when norm        // and lightDir are the same)
    float energyReceived = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = energyReceived * lightColor;

    // Specular Lighting //
    // Arbitrarily set coefficient here
    float specularCoefficient = 0.5;

    // Calculates view direction vector between LightPos and FragPos; normalizes as     // above
    vec3 viewDir = normalize(viewPos - FragPos);
    // Reflects lightDir about the norm (if viewDir == this resulting vector, 
    // then the greater the impact of specular light had on object
    vec3 reflectDir = reflect(-lightDir, norm);

    // Dot product will be the reflection of light source with the surface
    // and we take the max of this and 0 to calculate spec
    // Here, we also set the shininess value as 32 (smaller p results in
    // a wider lighting area)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularCoefficient * spec * lightColor;  

    // If gl_Position was set correctly, this gives a totally red cube
    //color = vec4(vec3(1.f,0.f,0.f), 1.0f);

    // Combine all components together
    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0f);
} 
