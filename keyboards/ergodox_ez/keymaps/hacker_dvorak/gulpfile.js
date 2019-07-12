let gulp = require('gulp');
let run = require('gulp-run-command').default;


gulp.task('clean', run('rm -rf ../../../../.build'));

gulp.task('build', ['clean'], run('make -C ../../../../ ergodox_ez:hacker_dvorak', {
    ignoreErrors: true
}));

gulp.task('watch', ['build'], () => {
    gulp.watch([
        'keymap.c',
        'config.h',
        'rules.mk',
    ], ['build']);
});

gulp.task('default', ['watch']);
