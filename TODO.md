# TODO - Lo que falta por implementar

## 1. Builtins (Prioridad ALTA)
- [X] echo con -n
- [X] cd (cambiar directorio con chdir)
- [X] pwd (mostrar directorio con getcwd)
- [X] export (añadir/modificar variables de entorno)
- [X] unset (eliminar variables de entorno)
- [X] env (mostrar todas las variables)
- [X] exit (salir del shell)

## 2. Variables de entorno (Prioridad ALTA)
- [X] Expandir $VAR, $USER, $PATH, etc.
- [X] Expandir $? (exit status del último comando)
- [X] Integrar expansión en el lexer
- [X] Arreglar var global de last_exit_status para $?
- [ ] Hacer que funcionen en el heredoc

## 3. Memoria y limpieza (Prioridad MEDIA)
- [ ] free_tokens() - Liberar lista de tokens
- [ ] free_cmd_list() - Liberar lista de comandos
- [ ] free_redir_list() - Liberar redirecciones
- [ ] Verificar con valgrind (no debe haber leaks)

## 4. Gestión de variables de entorno (Prioridad MEDIA)
- [X] Crear copia local de envp (para export/unset)
- [X] Actualizar envp cuando se hace export
- [X] Pasar envp actualizado a los comandos

## 5. Arreglar HEREDOC
- [X] Arreglar heredoc para que cuando no se le pase archivo
- [X] No funciona este comando: cat << EOF | grep test
- [X] Arreglar la función execute_pipeline (parte añadida)
- [ ] No funciona este comando: cat << EOF1 << EOF2

## 6. Extras
- [ ] Welcome to the Minishell

## 6. Pijadas
- [ ] Poner pwd en el readline

---