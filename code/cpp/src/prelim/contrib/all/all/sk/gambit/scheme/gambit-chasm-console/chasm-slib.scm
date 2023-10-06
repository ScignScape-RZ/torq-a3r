
(c-declare "extern int inc ();") ;;c functions must be declared
(c-declare "extern void test_symbol ();") ;;c functions must be declared
(c-declare "extern void test_kw ();") ;;c functions must be declared
(c-declare "extern void test_fn ();") ;;c functions must be declared


(define inc (c-lambda (int) int "inc")) ;;function implemented in C code
(define test-symbol (c-lambda (scheme-object) void "test_symbol")) ;;function implemented in C code
(define test-kw (c-lambda (scheme-object) void "test_kw")) ;;function implemented in C code

(define fn.- (c-lambda (scheme-object) void "test_fn")) ;;function implemented in C code

(define <- (c-lambda (scheme-object scheme-object) void "test_chin")) ;;function implemented in C code
(define >- (c-lambda (scheme-object scheme-object) void "test_chout")) ;;function implemented in C code

(define expr-proceed (c-lambda (scheme-object) void "expr_proceed")) ;;function implemented in C code

(define store-expr-proceed (c-lambda (scheme-object scheme-object) void "store_expr_proceed")) ;;function implemented in C code

(define get-expr-proceed (c-lambda () scheme-object "get_expr_proceed"))
(define expr-writer (c-lambda (scheme-object) scheme-object "expr_writer")) ;;function implemented in C code

(define get-expr-proceed-1 (c-lambda (scheme-object) scheme-object "get_expr_proceed_1"))


(c-define (scm-symbol->chars x) (scheme-object) char-string "scm_symbol_to_chars" "extern"
         (symbol->string x) )

(c-define (scm-kw->chars x) (scheme-object) char-string "scm_kw_to_chars" "extern"
         (keyword->string x) )

(c-define (inc-c x) (int) int "incc" "extern"
         (+ x 2))

;(c-define (inc x) (int) int "inc" "extern"
;         (+ x 1))

;(c-define (fib x) (int) int "fib" "extern"
;          (if (or  (= x 0)
;                   (= x 1))
;              x
;              (+ (fib (- x 1))
;                 (fib (- x 2)))))

(c-define (say_hello n) (char-string) char-string "say_hello" "extern"
  (string-append "Hello " n "!"))

;;copied from $GAMBIT/test/server.scm
(define (catch-all-errors thunk)
  (with-exception-catcher
   (lambda (exc)
     (write-to-string exc))
   thunk))

(define (write-to-string obj)
  (with-output-to-string
    '()
    (lambda () (write obj))))

(define (read-from-string str)
  (with-input-from-string str read))

; The following "c-define" form will define the function "eval_string"
; which can be called from C just like an ordinary C function.  The
; single argument is a character string (C type "char*") and the
; result is also a character string.

(c-define (eval-string str) (char-string) char-string "eval_string" "extern"
  (catch-all-errors
   (lambda ()
    ;(write "in eval string ...")
    (write-to-string (eval (read-from-string str))))))



;(input-port-readtable-set!
; (current-input-port)
; (readtable-keywords-allowed?-set
;  (current-readtable)
; #f
; )
;)

;(output-port-readtable-set!
; (current-output-port)
; (readtable-keywords-allowed?-set
;  (current-readtable)
; #f
; )
;)


(c-define (start-repl) () void "start_repl" "extern"
          (##start-repl-server "localhost:44555")
          (pp "read ")
          (read)
          (pp "done")
          )


