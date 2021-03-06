;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname 1.6.2) (read-case-sensitive #t) (teachpacks ((lib "drawings.ss" "installed-teachpacks"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "drawings.ss" "installed-teachpacks")) #f)))
(define rep
  (lambda (num b)
    ( let ((r (remainder num b))
           (q (quotient num b))
       )
    (if (< num b)
        (digit r)
        (string-append
         (rep q b)
         (digit r)
         )
        ))
    ))

(define digit
  (lambda (v)
    (string
     (integer->char
      (+ 
       v
       (char->integer #\0)
       )))
    ))