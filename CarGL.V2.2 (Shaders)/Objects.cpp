
/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    2012 - 2022 (C) Juan Antonio Puchol García (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include <GL/glui.h>

#include "load3ds.c"
#include "loadjpeg.c"
// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat light2_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light2_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light2_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light2_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -9.0 };

float coloresc_c[2][4] = { {0.8, 0.5, 0.0, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Color del coche
float coloresr_c[2][4] = { {0.3, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de la carretera

//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t)
{

    ID   = DL;
    tipo = t;
    prim=0;
    sx = sy = sz = 1;
    rx = ry = rz = 0;
    gr;
    gc;
	switch (tipo) {
		case CARRETERA_ID: {  // Creación de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Road.3ds", &num_vertices0);

            break;
		}
		case OBSTACULOS_ID: {  // Creación de la carretera
		    tz = tx= ty =0;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/obstaculos.3ds", &num_vertices0);		    tz = ty = tx =0;
            break;
		}
		case COCHE_ID: { // Creación del coche

		    tx =  0.0;
		    ty =  0.43;
		    tz =  0.0;
		    rr =  0.0;
		    memcpy(colores, coloresc_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/FordF250.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/rueda.3ds", &num_vertices1);
            modelo2 = Load3DS("../../Modelos/marcador.3ds", &num_vertices2);
            break;
		}
            case COCHE_ID+1: { // Creación del coche
		    tx =  0.0;
		    ty =  0.9;
		    tz =  0.0;
		    rr =  0.0;
		    memcpy(colores, coloresc_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/mariokarto2.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/rueda.3ds", &num_vertices1);
            break;
		}
            case ARBOLITO_ID: {  // Creación de la carretera
		    tz = tx =0;
		    ty=30;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/arbolito.3ds", &num_vertices0);
            break;
		}
            case BARRIL_ID: {  // Creación de la carretera
		    tz = tx =0;
		    ty = 2.45;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/barril.3ds", &num_vertices0);
            break;
		}
            case BLOQUECITO_ID: {
		    tz = tx =0;
		    ty=0.75;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/bloquecito.3ds", &num_vertices0);
            break;
		}
            case CARTELITO_ID: {  // Creación de la carretera
		    tz = tx =0;
		    ty = 5;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/cartelito.3ds", &num_vertices0);
            break;
		}
            case CASITA_ID: {  // Creación de la carretera
		    tz = tx=0;
		    ty=3.7;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/casita.3ds", &num_vertices0);
            break;
		}
            case CENTRO_ID: {  // Creación de la carretera
		    tz = ty = tx =0;
		    memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/centro.3ds", &num_vertices0);
            break;
		}
            case ESTRELLITA_ID: {  // Creación de la carretera
		    tz = tx=0;
		    ty=1.3;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/estrellita.3ds", &num_vertices0);
            break;
		}
            case MEGAFONOS_ID: {  // Creación de la carretera
		    tz = tx=0;
		    ty=5.1;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/megafonos.3ds", &num_vertices0);
            break;
		}
            case PANEL_ID: {  // Creación de la carretera
		    tz = ty = tx =0;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/panel.3ds", &num_vertices0);
            break;
		}
            case PAYASO_ID: {  // Creación de la carretera
		    tz = tx=0;
		    ty=6;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/payaso.3ds", &num_vertices0);
            break;
		}
            case TUBERIA_ID: {  // Creación de la carretera
		    tz = tx =0;
		    ty=5.2;
            memcpy(colores, coloresr_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/tuberia.3ds", &num_vertices0);
            break;
		}

	} // switch
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    switch (tipo) {

        case CARRETERA_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[0]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        } // case CARRETERA_ID:
        case OBSTACULOS_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[1]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                case ARBOLITO_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[2]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                case BARRIL_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[3]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                case BLOQUECITO_ID: {
            if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[4]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                case CARTELITO_ID: {
            if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[5]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                case CASITA_ID: {
            if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[6]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                case CENTRO_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[7]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                case ESTRELLITA_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[8]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                    case MEGAFONOS_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[9]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                    case PANEL_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[10]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
                    case PAYASO_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[11]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }

                    case TUBERIA_ID: {
                if (escena.show_road) {
                // Clculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0)); // rotaci�n alrededor del eje y en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[12]);
                glActiveTexture(GL_TEXTURE0);

                //                   Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case COCHE_ID: {

            glStencilFunc(GL_ALWAYS, this->ID, 0xFF);
            float dx,dz,cex,cez,tix,tiz;
            if (escena.show_car) {


                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[13]);
                glActiveTexture(GL_TEXTURE0);

                // Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                // C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc), glm::vec3(0,1,0));


                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

                if(marcador == 1){
                    //Marcador
                    glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                    glUniform1f(escena.uTextureUnitLocation, 0);
                    glBindTexture(GL_TEXTURE_2D,escena.texturas[2]);
                    glActiveTexture(GL_TEXTURE0);

                    //Asociamos los v�rtices y sus normales
                    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
                    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+3);
                    glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+6);


                    if(tmy >= 1.0){
                        aux = -1;
                    }

                    if(tmy <= 0){
                        aux = 1;
                    }

                    tmy += aux * 0.005;

                    modelMatrix     = glm::mat4(1.0f); // matriz identidad
                    modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, tmy+3.0, tz));
                    modelViewMatrix = escena.viewMatrix * modelMatrix;
                    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                    glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
                }
            }


            if (escena.show_wheels)
            {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                glUniform1f(escena.uTextureUnitLocation, 0);
                glBindTexture(GL_TEXTURE_2D,escena.texturas[14]);
                glActiveTexture(GL_TEXTURE0);

                // Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);
                if(gr < 45 ){
                    gr = gr;
                } else{
                    gr = 45;
                }

                // RUEDA Delantera Izquierda : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                dx = tx + 0.95*cos(glm::radians(gc));
                dz = tz - 0.95*sin(glm::radians(gc));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(dx, ty, dz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gr+gc), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Delantera Derecha : C�lculo de la matriz modelo HECHA
                modelMatrix     = glm::mat4(1.0f); // matriz identidad


                dx = tx - 0.95*cos(glm::radians(gc));
                dz = tz + 0.95*sin(glm::radians(gc));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(dx, ty,dz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc+gr), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Izquierda : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                cex = (-3.2 * sin(glm::radians(gc)));
                cez = (-3.2 * cos(glm::radians(gc)));
                tix = (tx + cex + 0.95*cos(glm::radians(gc)));
                tiz = (tz + cez  - 0.95*sin(glm::radians(gc)));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tix, ty, tiz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Derecha : C�lculo de la matriz modelo HECHO
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                cex = (-3.2 * sin(glm::radians(gc)));
                cez = (-3.2 * cos(glm::radians(gc)));
                tix = (tx + cex - 0.95*cos(glm::radians(gc)));
                tiz = (tz + cez + 0.95*sin(glm::radians(gc)));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tix, ty, tiz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gc), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

            }
            break;
        } // case COCHE_ID:
        case COCHE_ID+1: {
            if (escena.show_car) {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                // Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }


            if (escena.show_wheels)
            {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                // RUEDA Delantera Izquierda : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+1.1, ty-0.4, tz+1.3));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes
                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Delantera Derecha : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-1.1, ty-0.4, tz+1.3));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Izquierda : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+1.1, ty-0.5, tz-1.5));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(1.3,1.3,1.3));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Derecha : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-1.1, ty-0.5, tz-1.5));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(1.25,1.25,1.25));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

            }
            break;
        } // case COCHE_ID:
    } // switch

}

//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 1;
    num_objects = 0;
    num_cars = 0;

    cam = 0;
    vista = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 100.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(light2_ambient, light2_ambient_c, 4*sizeof(float));
    memcpy(light2_diffuse, light2_diffuse_c, 4*sizeof(float));
    memcpy(light2_specular, light2_specular_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Habilitamos plantillas
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Inicializaci�n de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    //std::cout << "Vertex Shader: " << shader.ReturnShaderID() << std::endl;
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    //std::cout << "Fragment Shader: " << shader.ReturnShaderID() << std::endl;
    shaderProgram = new Program(shaders);

    //std::cout << "Shader Program: " << shaderProgram->ReturnProgramID() << std::endl;

    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);
    aUVLocation=shaderProgram->attrib(A_UV);

    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);
    uTextureUnitLocation=shaderProgram->uniform(U_TEXTUREUNIT);
    uLuz0Location=shaderProgram->uniform(U_LUZ0);
    uLuz1Location=shaderProgram->uniform(U_LUZ1);
    uLuz2Location=shaderProgram->uniform(U_LUZ2);
    uInt0Location=shaderProgram->uniform(U_INT0);
    uInt1Location=shaderProgram->uniform(U_INT1);
    uInt2Location=shaderProgram->uniform(U_INT2);

    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);


    // Estableciendo la matriz de proyecci�n perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glActiveTexture(GL_TEXTURE0);
    glUniform1f(uTextureUnitLocation, 0);
    glGenTextures(CANTEXT,texturas);
    char *texturasGC[CANTEXT] = {"../../Modelos/Texturas/Carretera.jpg",
    "../../Modelos/Texturas/Obstaculos.jpg",
    "../../Modelos/Texturas/Arbol.jpg",
    "../../Modelos/Texturas/Barril.jpg",
    "../../Modelos/Texturas/Bloque.jpg",
    "../../Modelos/Texturas/Cartel.jpg",
    "../../Modelos/Texturas/Casita.jpg",
    "../../Modelos/Texturas/Centro.jpg",
    "../../Modelos/Texturas/Barril.jpg",
    "../../Modelos/Texturas/Bloque.jpg",
    "../../Modelos/Texturas/Panel.jpg",
    "../../Modelos/Texturas/Obstaculos.jpg",
    "../../Modelos/Texturas/Tuberia.jpg",
    "../../Modelos/Texturas/Coche.jpg",
    "../../Modelos/Texturas/Rueda.jpg",
    };
    for(int i = 0; i < CANTEXT ; i++){

        pixeles = LoadJPEG(texturasGC[i],&ancho, &alto);
        glBindTexture(GL_TEXTURE_2D, texturas[i]);
        printf("ancho %d   ",ancho);
        printf("alto   %d   ",alto);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixeles);
        free(pixeles);

        if(glIsTexture(escena.texturas[i])){
                std::cout << "cargada " << escena.texturas[i] << std::endl;
        }
        else{
            std::cout << "no cargada " << escena.texturas[i] << std::endl;
        }
    }
    glEnableVertexAttribArray(aUVLocation);
}


/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }

    }
    return(p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i=0; i<num_cars; i++)
    {
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //DIFERENTES CAMS
        switch (cam) {
        case 0: // Cámara actual (creada con los controles GLUI)
        {
            viewMatrix      = glm::mat4(1.0f);
            rotateMatrix    = glm::make_mat4(view_rotate);
            viewMatrix      = glm::translate(viewMatrix,glm::vec3(view_position[0], view_position[1], view_position[2]));
            viewMatrix      = viewMatrix*rotateMatrix;
            viewMatrix      = glm::scale(viewMatrix,glm::vec3(scale/100.0, scale/100.0, scale/100.0));
                break;
        }
        case 1: // Cámara de seguimiento
        {

            TPrimitiva *car = NULL;
            car = GetCar(escena.seleccion);
            viewMatrix      = glm::mat4(1.0f);
            // Obtén las coordenadas del coche y otras variables necesarias
            float cosCar = -10*cos(glm::radians(car->gc));
            float sinCar = -10*sin(glm::radians(car->gc));

            // Calcula los vectores Eye, Center, Up para la cámara aérea
            glm::vec3 eye = glm::vec3(car->tx+sinCar, car->ty+3, car->tz+cosCar);
            glm::vec3 center = glm::vec3(car->tx, car->ty+3, car->tz);
            glm::vec3 up = glm::vec3(0, 1, 0);

            // Crea la matriz de vista (cámara) utilizando glm::lookAt
            viewMatrix = glm::lookAt(eye, center, up);
                break;

        }
        case 2: // Cámara aérea
        {
            TPrimitiva *car = NULL;
            car = GetCar(escena.seleccion);
            viewMatrix      = glm::mat4(1.0f);
            glm::vec3 eye = glm::vec3(car->tx, car->ty+50, car->tz);
            glm::vec3 center = glm::vec3(car->tx+3, car->ty, car->tz);
            glm::vec3 up = glm::vec3(0, 0, 1);
            viewMatrix      = glm::lookAt(eye, center, up);
                break;
        }
    }
        //Modo de vista de la camara
    if(vista == 0){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if(vista == 1){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if(vista == 2){
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    //Culling
    if(culling == 1){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } else {
        glDisable(GL_CULL_FACE);
    }

    //Z-BUFFER
    if(z_buffer == 1){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniform1i(uLuz1Location, gui.light1_enabled);
    glUniform1i(uLuz2Location, gui.light2_enabled);
    glUniform1f(uInt0Location, gui.light0_intensity);
    glUniform1f(uInt1Location, gui.light1_intensity);
    glUniform1f(uInt2Location, gui.light2_intensity);
    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!
    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    glutSwapBuffers();
}

// Selecciona un objeto a través del ratón
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y)
{
    int index;
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    int y = h - mouse_y;
    glReadPixels(mouse_x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    TPrimitiva *car1 = NULL;
    car1 = GetCar(1);
    car1->colores[0][0] = 1;
    car1->marcador = false;

    TPrimitiva *car2 = NULL;
    car2 = GetCar(2);
    car2->colores[0][0] = 1;
    car2->marcador = false;

    if(index >= 0){
        escena.seleccion = index;

        TPrimitiva *car = NULL;
        car = GetCar(escena.seleccion);
        //car->colores[0][0] = 0.5;
        car->marcador = true;

        gui.radio -> set_int_val(escena.seleccion);
    }
}

// Crea todo el escenario
void __fastcall TEscena::CrearEscenario()
{
    TPrimitiva *road = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *car1 = new TPrimitiva(1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(2, COCHE_ID);
    TPrimitiva *obstaculos = new TPrimitiva(OBSTACULOS_ID, OBSTACULOS_ID);
    TPrimitiva *arbolito = new TPrimitiva(ARBOLITO_ID, ARBOLITO_ID);
    TPrimitiva *arbolito2 = new TPrimitiva(ARBOLITO_ID, ARBOLITO_ID);
    TPrimitiva *arbolito3 = new TPrimitiva(ARBOLITO_ID, ARBOLITO_ID);
    TPrimitiva *barril = new TPrimitiva(BARRIL_ID, BARRIL_ID);
    TPrimitiva *bloquecito = new TPrimitiva(BLOQUECITO_ID, BLOQUECITO_ID);
    TPrimitiva *bloquecito2 = new TPrimitiva(BLOQUECITO_ID, BLOQUECITO_ID);
    TPrimitiva *bloquecito3 = new TPrimitiva(BLOQUECITO_ID, BLOQUECITO_ID);
    TPrimitiva *bloquecito4 = new TPrimitiva(BLOQUECITO_ID, BLOQUECITO_ID);
    TPrimitiva *cartelito = new TPrimitiva(CARTELITO_ID, CARTELITO_ID);
    TPrimitiva *cartelito2 = new TPrimitiva(CARTELITO_ID, CARTELITO_ID);
    TPrimitiva *cartelito3 = new TPrimitiva(CARTELITO_ID, CARTELITO_ID);
    TPrimitiva *cartelito4 = new TPrimitiva(CARTELITO_ID, CARTELITO_ID);
    TPrimitiva *casita = new TPrimitiva(CASITA_ID, CASITA_ID);
    TPrimitiva *casita2 = new TPrimitiva(CASITA_ID, CASITA_ID);
    TPrimitiva *casita3 = new TPrimitiva(CASITA_ID, CASITA_ID);
    TPrimitiva *centro = new TPrimitiva(CENTRO_ID, CENTRO_ID);
    TPrimitiva *estrellita = new TPrimitiva(ESTRELLITA_ID, ESTRELLITA_ID);
    TPrimitiva *megafonos = new TPrimitiva(MEGAFONOS_ID, MEGAFONOS_ID);
    TPrimitiva *megafonos2 = new TPrimitiva(MEGAFONOS_ID, MEGAFONOS_ID);
    TPrimitiva *megafonos3 = new TPrimitiva(MEGAFONOS_ID, MEGAFONOS_ID);
    TPrimitiva *megafonos4 = new TPrimitiva(MEGAFONOS_ID, MEGAFONOS_ID);
    TPrimitiva *megafonos5 = new TPrimitiva(MEGAFONOS_ID, MEGAFONOS_ID);
    TPrimitiva *megafonos6 = new TPrimitiva(MEGAFONOS_ID, MEGAFONOS_ID);
    TPrimitiva *megafonos7 = new TPrimitiva(MEGAFONOS_ID, MEGAFONOS_ID);
    TPrimitiva *megafonos8 = new TPrimitiva(MEGAFONOS_ID, MEGAFONOS_ID);
    TPrimitiva *payaso = new TPrimitiva(PAYASO_ID, PAYASO_ID);
    TPrimitiva *payaso2 = new TPrimitiva(PAYASO_ID, PAYASO_ID);
    TPrimitiva *payaso3 = new TPrimitiva(PAYASO_ID, PAYASO_ID);
    TPrimitiva *payaso4 = new TPrimitiva(PAYASO_ID, PAYASO_ID);
    TPrimitiva *tuberia = new TPrimitiva(TUBERIA_ID, TUBERIA_ID);
    TPrimitiva *tuberia2 = new TPrimitiva(TUBERIA_ID, TUBERIA_ID);
    TPrimitiva *tuberia3 = new TPrimitiva(TUBERIA_ID, TUBERIA_ID);

    car2->colores[0][0] = 0.1;
    car2->colores[0][1] = 0.4;
    car2->colores[0][2] = 0.9;
    car2->colores[0][3] = 1.0;
    car2->tx = 2;
    car2->tz = 4;
    car1->tz= -4;
    car1->marcador=false;
    car2->marcador=false;

    road->colores[0][1]=0.8;

    arbolito->tx=50;arbolito->tz=50;
    arbolito2->tx=100;arbolito2->tz=-70;
    arbolito3->tx=-110;arbolito3->tz=100;
    barril->tx=30;barril->tz=30;
    obstaculos->ty=1.2;
    bloquecito->tx=10;
    bloquecito2->tx=10;bloquecito2->tz=3;
    bloquecito3->tx=10;bloquecito3->tz=-3;
    bloquecito4->tx=10;bloquecito4->tz=6;
    cartelito->tx=-50;
    cartelito2->tx=50;cartelito2->ry=180;
    cartelito3->tz=50;cartelito3->ry=90;
    cartelito4->tz=-50;cartelito4->ry=270;
    casita->tx=40;casita->tz=-40;
    casita2->tx=-40;casita2->tz=40;
    casita3->tx=-40;casita3->tz=-40;
    megafonos->tx=22;megafonos->tz=45;
    megafonos2->tx=-22;megafonos2->tz=-45;
    megafonos3->tx=22;megafonos3->tz=-45;
    megafonos4->tx=-22;megafonos4->tz=45;
    megafonos5->tx=45;megafonos5->tz=22;
    megafonos6->tx=-45;megafonos6->tz=-22;
    megafonos7->tx=45;megafonos7->tz=-22;
    megafonos8->tx=-45;megafonos8->tz=22;
    payaso->tx=55;payaso->tz=10;
    payaso2->tx=-55;payaso2->tz=10;
    payaso3->tz=55;payaso3->tx=-10;
    payaso4->tz=-55;payaso4->tx=-10;
    estrellita->tx=4;estrellita->tz=4;
    tuberia->tx=40;tuberia->tz=-30;
    tuberia2->tx=-40;tuberia2->tz=30;
    tuberia3->tx=-40;tuberia3->tz=-30;
    // Añadir objetos
    AddObject(road);
    AddObject(obstaculos);
    AddObject(arbolito);AddObject(arbolito2);AddObject(arbolito3);
    AddObject(barril);
    AddObject(bloquecito);AddObject(bloquecito2);AddObject(bloquecito3);AddObject(bloquecito4);
    AddObject(cartelito);AddObject(cartelito2);AddObject(cartelito3);AddObject(cartelito4);
    AddObject(casita);AddObject(casita2);AddObject(casita3);
    //AddObject(centro);
    AddObject(estrellita);
    AddObject(megafonos);AddObject(megafonos2);AddObject(megafonos3);AddObject(megafonos4);AddObject(megafonos5);AddObject(megafonos6);AddObject(megafonos7);AddObject(megafonos8);
    //AddObject(panel);AddObject(panel2);AddObject(panel3);AddObject(panel4);
    AddObject(payaso);AddObject(payaso2);AddObject(payaso3);AddObject(payaso4);
    AddObject(tuberia);AddObject(tuberia2);AddObject(tuberia3);
    // Añadir coches
    AddCar(car1);
    AddCar(car2);
}

//************************************************************** Clase TGui

TGui::TGui()
{
    sel = 1;
    cam = 0;
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light2_enabled = 1;
    light0_intensity = 0.2;
    light1_intensity = 0.019;
    light2_intensity = 0.2;
    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        Código con el interfaz Gráfico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    // Añade un panel con texto con el valor de la selección
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Seleccion");
    GLUI_RadioGroup *radioGroup = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup, "NINGUNO");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 1");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 2");

    gui.radio = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    // Añade camaras
    GLUI_Panel *panelcams = new GLUI_Panel(glui, "Camaras");
    GLUI_RadioGroup *radiocams = new GLUI_RadioGroup(panelcams, &cam, CAMS_ID, controlCallback);
    glui->add_radiobutton_to_group(radiocams, "Libre");
    glui->add_radiobutton_to_group(radiocams, "Seguimiento");
    glui->add_radiobutton_to_group(radiocams, "Aérea");
    //MODO VISTA
    GLUI_Panel *panelvista = new GLUI_Panel(glui, "Vista");
    GLUI_RadioGroup *radiovista = new GLUI_RadioGroup(panelvista, &vista, MODOVISTA_ID, controlCallback);
    glui->add_radiobutton_to_group(radiovista, "Normal");
    glui->add_radiobutton_to_group(radiovista, "Wireframe");
    glui->add_radiobutton_to_group(radiovista, "Puntos");
    // Añade una separación
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );

    /***** Control para las propiedades de escena *****/

    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, 1, controlCallback );

    /******** Añade controles para las luces ********/

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", true );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );
    GLUI_Panel *light2 = new GLUI_Panel( roll_lights, "Luz 3" );
    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensidad:", &light1_intensity,
                            LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light1, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[0],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[1],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[2],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light2, "Encendida", &light2_enabled, LIGHT2_ENABLED_ID, controlCallback );
    light2_spinner = new GLUI_Spinner( light2, "Intensidad:", &light2_intensity,
                            LIGHT2_INTENSITY_ID, controlCallback );
    light2_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light2, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[0],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light2, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[1],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light2, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[2],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);


    // Añade una separación
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", false );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Carretera", &escena.show_road );


    /*** Disable/Enable botones ***/
    // Añade una separación
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Permitir Movimiento", &enable_panel2 );
    // Añade una separación
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Autor:" );
    new GLUI_StaticText( glui, "  2012-2022 (C) Juan Antonio Puchol  " );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate );
    view_rot->set_spin( 1.0 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position );
    trans_xy->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position );
    trans_x->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1] );
    trans_y->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.scale );
    trans_z->set_speed( .005 );

}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT2_ENABLED_ID: {
            if ( light2_enabled )
                light2_spinner->enable();
            else
                light2_spinner->disable();
            break;
        }
        case LIGHT2_INTENSITY_ID: {

            float v[] = {
                escena.light2_diffuse[0],  escena.light2_diffuse[1],
                escena.light2_diffuse[2],  escena.light2_diffuse[3] };

            v[0] *= light2_intensity;
            v[1] *= light2_intensity;
            v[2] *= light2_intensity;
            break;
        }
        case LIGHT0_INTENSITY_ID: {

            float v[] = {
                escena.light0_diffuse[0],  escena.light0_diffuse[1],
                escena.light0_diffuse[2],  escena.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            break;
        }
        case LIGHT1_INTENSITY_ID: {

            float v[] = {
                escena.light1_diffuse[0],  escena.light1_diffuse[1],
                escena.light1_diffuse[2],  escena.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            break;
        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {
            memcpy(escena.view_position,view_position_c,3*sizeof(float));
            view_rot->reset();
            escena.scale = 100.0;
            break;
        }
        case SEL_ID: {
            escena.seleccion = sel;
            //gui.radio->set_int_val(sel);
            //GLUI_Master.SetFocus(true);
            TPrimitiva *car1 = escena.GetCar(1);
            car1->marcador = false;

            TPrimitiva *car2 = escena.GetCar(2);
            car2->marcador = false;

            if(sel > 0){
                TPrimitiva *car = escena.GetCar(sel);
                car->marcador = true;
            }
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
            case CAMS_ID: {
            escena.cam = cam;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
            case MODOVISTA_ID: {
            escena.vista = vista;
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }

  } // switch
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */
    if (enable_panel2)

        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int xx, int yy )
{
    int x, y, ancho, alto;
    GLUI_Master.get_viewport_area( &x, &y, &ancho, &alto );
    glViewport( x, y, ancho, alto );

    // !!!!! ATENCIÓN: comprobar que alto no sea 0, sino división por 0 !!!!!!
    escena.xy_aspect = (float)ancho / (float)alto;
    escena.projectionMatrix = glm::perspective(45.0f, escena.xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));

    //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    if(button_state == GLUT_DOWN){
        escena.last_x = x;
        escena.last_y = y;
    } else if(button_state == GLUT_UP){
        escena.Pick3D(x, y);
    }
}

