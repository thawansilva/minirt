## Plan: miniRT Input Validation Feature

TL;DR: build a robust parser/validator for .rt scenes in `src/validation/input.c`, with full object rules and CMocka tests. Use explicit error messages and exit as required.

Steps
1. Setup project scaffolding:
   - Verify `Makefile` includes validation source compilation.
   - Ensure `tests/Makefile` runs CMocka tests.
2. Define core data structures in `inc/minirt.h`:
   - `t_vec3`, `t_color`.
   - `t_camera`, `t_light`, `t_sphere`, `t_plane`, `t_cylinder`.
   - `t_scene` with counters and linked lists/arrays.
3. Implement a general parser framework in `src/validation/input.c`:
   - `validate_extension(char *file)` ensures `.rt` extension.
   - `read_file(char *file, t_scene *scene, char **error)`.
   - line tokenizer using `ft_split` on spaces.
   - object dispatcher: `A`, `C`, `L`, `sp`, `pl`, `cy`.
   - per-line duplicate check for one-time objects (A/C/L).
   - global min/max object count checks after parsing.
4. Implement per-component validators:
   - `validate_vector(char *token, t_vec3 *out)` coordinate range is any float; includes numeric format.
   - `validate_normal(char *token, t_vec3 *out)` with -1..1 and non-zero length.
   - `validate_fov(char *token, int *out)` range 0..180.
   - `validate_ratio(char *token, double *out)` range 0..1 for lights.
   - `validate_rgb(char *token, t_color *out)` range 0..255.
   - cylinder height/diameter positive.
5. Integrate mandatory and bonus criteria in validation rules:
   - object type set exactly: A, C, L, sp, pl, cy (reject others).
   - one or more spaces allowed between tokens (parser from split handles this).
   - each line split fields count exactly for each type.
   - enforced: one ambient, one camera, one light (object ++). optionally allow >1 light? criteria says capital letter once.
   - min/max objects for mandatory: at least 1 camera, 1 light, 1 ambient, 1 shape. Decide exact bounds based on miniRT rubric (0..inf for shapes). Provide constants.
   - coordinates for positions direction etc must be valid floats.
6. Error output design:
   - function `print_error_and_exit(char *msg, int line_number)` prints "Error\n" + message and exits(1).
   - internal path: parse functions return status and fill error string for tests.
7. Testing targets:
   - unit tests for each validator function in `tests/test_input_validation.c`.
   - parser integration tests for small `.rt` strings.
   - failure tests for each validation rule: extension, type, duplicate A/C/L, malformed vector, out-of-range rgb, wrong token count, etc.
   - positive tests for valid examples.
8. Add extra criteria as robust features:
   - trailing spaces and blank lines are ignored.
   - comments (#) allowed (if desired) and ignored.
   - catastrophic IO errors (file missing/unreadable) are reported.

Relevant files
- `src/validation/input.c` — main implementation.
- `inc/minirt.h` — type declarations and constants.
- `src/main.c` — call validate_input and handle exit.
- `tests/test_main.c` and new `tests/test_input_validation.c`.

Verification
1. `make` builds without warnings and binary executes with valid scene.
2. `make test` runs CMocka and all new tests pass.
3. Run `./miniRT foo.rt` on invalid extension and check output is "Error\n" + message and nonzero exit status.
4. For each invalid case, test ensures error output and path.

Decisions
- Use explicit per-field validation rules to satisfy rubric.
- Parse line tokens with `ft_split` to allow multiple spaces.
- Use C-style return codes with error string to facilitate tests and `exit` in main.

Further Considerations
1. Should ambient/camera/light be exactly one or at least one?  
   - Recommend exactly one for capitals and object semantics.
2. Should file support comments?  
   - Optional enhancement; include if time.
3. Should shapes beyond `sp/pl/cy` be rejected immediately?  
   - For mandatory part, yes, to ensure strict scene format.
