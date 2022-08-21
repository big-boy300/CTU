#lang racket
(provide execute)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;FORMATTERS;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (format-svg-header w h)
  (format "<svg width=\"~a\" height=\"~a\">" w h))

(define (format-svg-body cmd [env ""])
  (match cmd
    [(list 'circle x y r style)
     (format "<circle cx=\"~a\" cy=\"~a\" r=\"~a\" style=\"~a\"/>" (math-eval x env) (math-eval y env) (math-eval r env) style)]
    [(list 'rect x y width height style)
     (format "<rect x=\"~a\" y=\"~a\" width=\"~a\" height=\"~a\" style=\"~a\"/>" (math-eval x env) (math-eval y env) (math-eval width env) (math-eval height env) style)]
    [(list 'line x1 y1 x2 y2 style)
     (format "<line x1=\"~a\" y1=\"~a\" x2=\"~a\" y2=\"~a\" style=\"~a\"/>" (math-eval x1 env) (math-eval y1 env) (math-eval x2 env) (math-eval y2 env) style)]
    [_ "DID NOT MATCH SVG COMMAND"]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;EVALUTORS;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (math-eval expr [env ""])
  (match expr
    [(? number? num) num] 
    [(list '+ args ...) (apply + (map (lambda (arg) (math-eval arg env)) args))]
    [(list '- args ...) (apply - (map (lambda (arg) (math-eval arg env)) args))]
    [(list '* args ...) (apply * (map (lambda (arg) (math-eval arg env)) args))]
    [(list '/ args ...) (apply / (map (lambda (arg) (math-eval arg env)) args))]
    [(list 'floor args ...) (apply floor (map (lambda (arg) (math-eval arg env)) args))]
    [(list 'cos args ...) (apply cos (map (lambda (arg) (math-eval arg env)) args))]
    [(list 'sin args ...) (apply sin (map (lambda (arg) (math-eval arg env)) args))]
    [_ (math-eval (hash-ref env expr) env)]))

(define (logic-eval expr [env ""])
  (match expr
    [(list '> arg1 arg2)(> (math-eval arg1 env) (math-eval arg2 env))]
    [(list '< arg1 arg2)(< (math-eval arg1 env) (math-eval arg2 env))]
    [(list '= arg1 arg2)(= (math-eval arg1 env) (math-eval arg2 env))]
    [_ "IMPOSSIBLE LOGICAL OPERATION"]))

(define (expr-eval expr [env ""])
  (match expr
    [(list 'if bool-exp exp1 exp2) (if (logic-eval bool-exp env) (expr-eval exp1 env) (expr-eval exp2 env))]
    [(list 'when bool-exp exp ...) (if (logic-eval bool-exp env) (rec-solver exp env) "")]
    [(list 'circle x y r style) (format-svg-body expr env)]
    [(list 'rect x y width height style) (format-svg-body expr env)]
    [(list 'line x1 y1 x2 y2 style) (format-svg-body expr env)]
    [(list func-name args ...)(rec-solver (func-storage-expr (hash-ref func-ht func-name))
                                          (fill-args-ht (func-storage-args(hash-ref func-ht func-name)) (map (lambda (arg-arg) (math-eval arg-arg env)) args)))]
    [(list func-name args ... exprs ...)(rec-solver (func-storage-expr(hash-ref func-ht func-name))
                                                   (fill-args-ht (func-storage-args(hash-ref func-ht func-name)) (map (lambda (arg-arg) (math-eval arg-arg env)) args)))]
    [_ "IMPOSSIBLE EXPRESSION"]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;DATA SRUCTURES AND HELPER FUNCTIONS;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;structure for arguments and body of functions defined in prg
(struct func-storage (args expr))

;;hashtable for all functions from prg, key is name of a function, value is structure with function's arguments and body 
(define func-ht (make-hash))

;;add structures to hash tables when there is a match
(define (match-func-defs prg)
  (match prg
    [(list 'define (list name) expr ...) (hash-set! func-ht name (func-storage '() expr))]
    [(list 'define (list name args ...) expr ...) (hash-set! func-ht name (func-storage args expr))]
    [_ "NO FUNCTION MATCHED"]))

;;for possible multiple function definitions in prg
(define (match-all prg)
  (map match-func-defs prg))

;;func to fill args hashtable
(define (fill-args-ht keys vals)
  (define args-ht (make-hash))
  (for ([k keys][v vals])(hash-set! args-ht k v))
  args-ht)

(define (rec-solver expr env [fin-str ""])
  (cond
    [(null? expr) fin-str]
    [else (rec-solver (cdr expr) env (append (list(expr-eval (car expr) env)) fin-str ))]))

(define (execute-full width height prg expr)
  (match-all prg)
  (if (null? (cdr expr))
      (string-append (string-append (format-svg-header width height)(foldr string-append "" (flatten (map expr-eval (func-storage-expr(hash-ref func-ht (car expr))))))) "</svg>")     
      (string-append (string-append (format-svg-header width height)
                                    (foldr string-append ""
                                           (reverse(flatten (rec-solver (func-storage-expr(hash-ref func-ht (car expr)))
                                                                        (fill-args-ht (func-storage-args (hash-ref func-ht (car expr))) (map math-eval (cdr expr))) ))))) "</svg>")))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;DIVER FUNCTION;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (execute width height prg expr)
  (cond
    [(null? prg) (string-append (string-append(format-svg-header width height)(foldr string-append "" (flatten (expr-eval expr)))) "</svg>")]
    [else (execute-full width height prg expr)]))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;