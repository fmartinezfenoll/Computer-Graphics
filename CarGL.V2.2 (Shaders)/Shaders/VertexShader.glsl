
attribute vec4 a_Position;	        // in: Posici?n de cada v?rtice
attribute vec3 a_Normal;	        // in: Normal de cada v?rtice
attribute vec2 a_UV;

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (c?mara)
uniform vec4 u_Color;		        // in: Color del objeto

uniform int  u_Luz0;                // in: Indica si la luz 0 est? encedida
uniform float u_Int0;
uniform int  u_Luz1;
uniform float u_Int1;
uniform int  u_Luz2;
uniform float u_Int2;

uniform vec4 u_Pos0 = vec4(-10.0f, 10.0f, 5.0f, 1.0f);
uniform vec4 u_Pos1 = vec4(0.0f, 10.0f, 0.0f, 1.0f);
uniform vec4 u_Pos2 = vec4(100.0f, 100.0f, 50.0f, 1.0f);

varying vec4 v_Color;		        // out: Color al fragment shader
varying vec2 v_UV;

void main()
{

    v_UV = a_UV;

    vec4 LightPos0 = u_VMatrix * u_Pos0;
    vec4 LightPos1 = u_VMatrix * u_Pos1;
    vec4 LightPos2 = u_VMatrix * u_Pos2;
    vec3 P = vec3(u_MVMatrix * a_Position);	            // Posici?n del v?rtice
	vec3 N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));    // Normal del v?rtice

	float d0 = length(LightPos0.xyz - P);			        // distancia de la luz
	vec3  L0 = normalize(LightPos0.xyz - P);			    // Vector Luz
	float d1 = length(LightPos1.xyz - P);
	vec3  L1 = normalize(LightPos1.xyz - P);
	float d2 = length(LightPos2.xyz - P);
	vec3  L2 = normalize(LightPos2.xyz - P);

	vec4 coordenadas = vec4(P.x, P.y, P.z, 1.0);
	vec4 matrizVista = vec4(u_VMatrix[3][0], u_VMatrix[3][1], u_VMatrix[3][2], u_VMatrix[3][0]);
	vec3 calculo = normalize(vec3(u_VMatrix * matrizVista * (vec4(0.0, 0.0, 0.0, 1.0) - coordenadas)));

	float ambient = 0.15;                               // (15% de int. ambiente)
	float diffuse = 0.0;
	float diffuseF = 0.0;

	float specular = 0.0;
	float specularF = 0.0;
	int especularidad = 25;

	if (u_Luz0>0) {                                     // Si la luz 0 est? encendida se calcula la intesidad difusa de L
        diffuse = max(dot(L0, N), 0.0);		            // C?lculo de la int. difusa
        // C?lculo de la atenuaci?n
        float attenuation = 10.0/(0.15+(0.01*d0)+(0.003*d0*d0));
        specular = attenuation * pow(max(0.0, dot(reflect(-L0, N), calculo)), especularidad);
        specularF += specular;
        diffuseF += diffuse*attenuation*u_Int0;
	}

	if (u_Luz1>0) {
        diffuse = max(dot(N, L1), 0.0);
        float attenuation = 80.0/(0.25+(0.01*d1)+(0.003*d1*d1));
        specular = attenuation * pow(max(0.0, dot(reflect(-L1, N), calculo)), especularidad);
        specularF += specular;
        diffuseF += diffuse*attenuation*u_Int1;
	}

    if (u_Luz2>0) {
        diffuse = max(dot(N, L1), 0.0);
        float attenuation = 80.0/(0.25+(0.01*d2)+(0.003*d2*d2));
        specular = attenuation * pow(max(0.0, dot(reflect(-L2, N), calculo)), especularidad);
        specularF += specular;
        diffuseF += diffuse*attenuation*u_Int2;
	}

	v_Color = u_Color * (ambient + diffuseF + (vec4(1,1,1,1) * specularF));
	gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}
