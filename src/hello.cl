void kernel simple_add(global int *a) {
    a[get_global_id(0)] = get_global_id(0);
    a[0] = 5;
}
