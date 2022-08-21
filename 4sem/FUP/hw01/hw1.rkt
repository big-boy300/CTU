#lang racket
(require 2htdp/image)
(provide img->mat
         ascii-art)

(define (RGB->grayscale color)
  (+ (* 0.3 (color-red color))
     (* 0.59 (color-green color))
     (* 0.11 (color-blue color))))

(define (lst->mat img lst [acc '()] [acc1 '()])
  (cond
    [(null? lst) (reverse(cons (reverse acc) acc1))]
    [(= (length acc) (image-width img)) (lst->mat img lst '() (cons (reverse acc) acc1))]
    [else (lst->mat img (cdr lst) (cons (car lst) acc) acc1)]))

(define (img->mat img)
  (lst->mat img (map RGB->grayscale (image->color-list img))))

(define (pop-last-elem lst)
  (cond
    [(null? lst) '()]
    [(null? (cdr lst)) '()]
    [else (cons(car lst) (pop-last-elem (cdr lst)))]))

(define (cut-list param lst [new-lst '()])
  (cond
    [(= (modulo (length lst) param) 0) lst]
    [else (cut-list param (pop-last-elem lst))]))

(define (cut-rows w mat [new-mat '()])
  (cond
    [(null? mat) (reverse new-mat)]
    [else (cut-rows w (cdr mat) (cons(cut-list w (car mat)) new-mat))]))

(define (average lst [sum 0] [elems 0])
  (cond
    [(= (length lst) 0) (/ sum elems)]
    [else (average (cdr lst) (+ (car lst) sum) (+ elems 1))]))

(define (lst-avg w lst [tmp '()] [new-lst '()])
  (cond
    [(and (null? lst) (null? tmp)) (reverse new-lst)]
    [(not (= (length tmp) w)) (lst-avg w (cdr lst) (cons(car lst) tmp) new-lst)]
    [else (lst-avg w lst '() (cons (average tmp) new-lst))]))

(define (change-mat-rows w mat [new-mat '()])
  (cond
    [(null? mat) (reverse new-mat)]
    [else (change-mat-rows w (cdr mat) (cons (lst-avg w (car mat)) new-mat))]))

(define (transpose-mat mat)
  (cond
    [(null? mat) '()]
    [(null? (car mat)) '()]
    [else (cons (map car mat) (transpose-mat(map cdr mat)))]))

(define (find-char chars-impl i [d (length (string->list chars-impl))])
  (cond
    [(= i 255) (list-ref (string->list chars-impl) 0)]
    [(= i 0) (list-ref (string->list chars-impl) (- d 1))]
    [else (list-ref (string->list chars-impl) (inexact->exact(floor (/ (* d (- 255 (floor i))) 256))))]))

(define (lst->chars chars-impl lst [new-lst '()])
  (cond
    [(null? lst) new-lst]
    [else (lst->chars chars-impl (cdr lst) (cons (find-char chars-impl (car lst)) new-lst))]))

(define (mat->chars chars-impl mat [new-mat '()])
  (cond
    [(null? mat) new-mat]
    [else (mat->chars chars-impl (cdr mat) (cons(lst->chars chars-impl (car mat)) new-mat))]))

(define (mat-char->string mat [str ""])
  (cond
    [(null? mat) (list->string(reverse (string->list str)))]
    [else (mat-char->string (cdr mat) (string-append str (string-append "\n" (list->string (car mat)))))]))

(define (ascii-art width height chars)
  (lambda (img)
    (mat-char->string
     (mat->chars chars
      (transpose-mat
       (change-mat-rows height (transpose-mat (change-mat-rows width (cut-list height (cut-rows width (img->mat img)))))))))))
       