precision mediump float;	// Precisi�n media, en algunas gr�ficas no se soporta (depende de la versi�n de GLSL), en ese caso comentar o quitar esta l�nea

uniform sampler2D u_TextureUnit;

varying vec2 v_UV;
varying vec4 v_Color;		// in: color del vertex shader

void main()
{
            vec4 t_Color;
            t_Color = texture2D(u_TextureUnit, v_UV);
            gl_FragColor = v_Color*t_Color;
}
