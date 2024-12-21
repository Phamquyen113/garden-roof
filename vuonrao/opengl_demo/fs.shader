#version 460
in vec3 position_eye, normal_eye;
uniform mat4 view_mat_shader;
uniform vec3 objectColor;
out vec4 out_color;

void main() {
   
    vec3 light_position_world = vec3(0.0, 2, -15);
    vec3 light_position_eye = vec3(view_mat_shader * vec4(light_position_world, 1.0));

   
    vec3 bulb_position_world = vec3(0, 50, 500); 
    vec3 bulb_position_eye = vec3(view_mat_shader * vec4(bulb_position_world, 1.0));

    vec3 position_viewer = vec3(0.0, 0.0, 0.0);
    vec3 n_eye = normalize(normal_eye);

    // Light calculations for main light source
    vec3 distance_to_light_eye = light_position_eye - position_eye;
    vec3 direction_to_light_eye = normalize(distance_to_light_eye);
    vec3 surface_to_viewer_eye = normalize(position_viewer - position_eye);

    float dot_prod = dot(direction_to_light_eye, n_eye);
    dot_prod = max(dot_prod, 0.0);
    vec3 Ld = vec3(0.8, 0.8, 0.8);
    vec3 Kd = vec3(1.0, 1.0, 1.0);
    vec3 Id = Ld * Kd * dot_prod;

    vec3 half_way_eye = normalize(surface_to_viewer_eye + direction_to_light_eye);
    float dot_prod_specular = dot(half_way_eye, n_eye);
    dot_prod_specular = max(dot_prod_specular, 0.0);

    float specular_exponent = 64.0;
    float specular_factor = pow(dot_prod_specular, specular_exponent);
    vec3 Ls = vec3(1.2, 1.2, 1.2);
    vec3 Ks = vec3(0.5, 0.5, 0.5);
    vec3 Is = Ls * Ks * specular_factor;

    vec3 La = vec3(0.5, 0.5, 0.5);
    vec3 Ka = vec3(1.0, 1.0, 1.0);
    vec3 Ia = La * Ka;

    
    vec3 distance_to_bulb_eye = bulb_position_eye - position_eye;
    vec3 direction_to_bulb_eye = normalize(distance_to_bulb_eye);

    float dot_prod_bulb = dot(direction_to_bulb_eye, n_eye);
    dot_prod_bulb = max(dot_prod_bulb, 0.0);
    vec3 Ld_bulb = vec3(0.3,0.3,0.3); 
    vec3 Id_bulb = Ld_bulb * Kd * dot_prod_bulb;

    vec3 half_way_bulb_eye = normalize(surface_to_viewer_eye + direction_to_bulb_eye);
    float dot_prod_specular_bulb = dot(half_way_bulb_eye, n_eye);
    dot_prod_specular_bulb = max(dot_prod_specular_bulb, 0.0);

    float specular_factor_bulb = pow(dot_prod_specular_bulb, specular_exponent);
    vec3 Ls_bulb = vec3(1.0, 0.9, 0.7); 
    vec3 Is_bulb = Ls_bulb * Ks * specular_factor_bulb;

   
    vec3 final_color = objectColor * (Id + Is + Ia + Id_bulb + Is_bulb);
    out_color = vec4(final_color, 1.0);
}
