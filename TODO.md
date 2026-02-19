# TODO - Lo que falta por implementar

## 1. Builtins (Prioridad ALTA)
- [ ] echo con -n
- [ ] cd (cambiar directorio con chdir)
- [ ] pwd (mostrar directorio con getcwd)
- [ ] export (añadir/modificar variables de entorno)
- [ ] unset (eliminar variables de entorno)
- [ ] env (mostrar todas las variables)
- [ ] exit (salir del shell)

## 2. Variables de entorno (Prioridad ALTA)
- [ ] Expandir $VAR, $USER, $PATH, etc.
- [ ] Expandir $? (exit status del último comando)
- [ ] Integrar expansión en el lexer

## 3. Memoria y limpieza (Prioridad MEDIA)
- [ ] free_tokens() - Liberar lista de tokens
- [ ] free_cmd_list() - Liberar lista de comandos
- [ ] free_redir_list() - Liberar redirecciones
- [ ] Verificar con valgrind (no debe haber leaks)

## 4. Gestión de variables de entorno (Prioridad MEDIA)
- [ ] Crear copia local de envp (para export/unset)
- [ ] Actualizar envp cuando se hace export
- [ ] Pasar envp actualizado a los comandos

---