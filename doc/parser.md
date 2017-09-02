# Basado en cadenas de fibers,
# lee y monitoriza un arbol de archivos
# manteniendo un AST sincronizado, los errores son reportados
# directamente sobre el codigo a traves de comentarios de escape

# chunker trocea la entrada de caracters en lineas


# AST:

Block:
  Line lines[];

Line: {
  tokens
  expr: EXPR
  identation: Block
}


a+b                               \xxx type mismatch: a and b are not same type
    comment
  a
      other comment
    sub
