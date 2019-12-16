#version 450

struct element
{
    vec4 p;
    vec4 f;
    vec4 v;
};

uniform uint size;
uniform uint fps;

layout(local_size_x=1) in;

layout(std430, binding = 0) buffer position_buffer
{
    element elem[];
};

float norm(vec4 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

vec4 force(vec4 s, vec4 x, float alpha1, float alpha2) {
    float diff = norm(s - x);
    return (alpha1 / (diff * diff) - alpha2 / (diff * diff * diff * diff)) * (s - x) / diff;
}

void update(int k)
{
    // Init
    const float dt = float(fps) / 200;
    elem[k].f = vec4(0, 0, 0, 0);

    // Loop with fishes
    if (k < 5) {
        for (int j = 0; j < size; ++j) {
            if (k != j && j != 5) {
                if (norm(elem[k].p - elem[j].p) < 0.5) {
                    elem[k].f += force(elem[j].p, elem[k].p, 1, 0.05);
                    elem[k].v -= 0.5 * (elem[k].v - elem[j].v);
                }
            }
            if (j == 5) {
                if (norm(elem[k].p - elem[j].p) < 1) {
                    elem[k].f += force(elem[j].p, elem[k].p, 0, 0.3);
                }
            }
        }
    }

    if (k == 5) {
        for (int j = 0; j < size; ++j) {
            if (k != j) {
                if (norm(elem[k].p - elem[j].p) < 1) {
                    elem[k].f += force(elem[j].p, elem[k].p, 2, 0);
                }
            }
            if (j == 5) {
                if (norm(elem[k].p - elem[j].p) < 1) {
                    elem[k].f += force(elem[j].p, elem[k].p, 0, 0.5);
                }
            }
        }
    }

    // Constraints fishes
    if (k < 5) {
        for (int i = 0; i < 3; ++i) {
            if (elem[k].v[i] < -1)
            elem[k].v[i] = -1;
            if (elem[k].v[i] > 1)
            elem[k].v[i] = 1;
            if (elem[k].p[i] < -2)
            elem[k].p[i] = 2;
            if (elem[k].p[i] > 2)
            elem[k].p[i] = -2;
        }
    }
    else {
        for (int i = 0; i < 3; ++i) {
            if (elem[k].v[i] < -2)
            elem[k].v[i] = -2;
            if (elem[k].v[i] > 2)
            elem[k].v[i] = 2;
            if (elem[k].p[i] < -2)
            elem[k].p[i] = 2;
            if (elem[k].p[i] > 2)
            elem[k].p[i] = -2;
        }
    }

    // Position update fishes
    elem[k].v = elem[k].v + dt * elem[k].f;
    elem[k].p = elem[k].p + dt * elem[k].v;
}

void main()
{
    update(int(gl_GlobalInvocationID.x));
}
