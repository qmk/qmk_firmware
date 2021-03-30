const gulp = require('gulp');
const run = require('gulp-run-command').default;


const ROOT_DIR = '../../../../';
const BUILD_DIR = `${ROOT_DIR}.build`;
const HACKER_DVORAK_DIR = './**/*';

const CLEAN_CMD = `rm -rf ${BUILD_DIR}`;
const BUILD_CMD = `make -C ${ROOT_DIR} ergodox_ez:hacker_dvorak`;

gulp.task('clean', run(CLEAN_CMD));

gulp.task('build', gulp.series('clean', run(BUILD_CMD, {
        ignoreErrors: true
})));

gulp.task('watch', gulp.series('build', () => {
    gulp.watch(HACKER_DVORAK_DIR, gulp.series('build'));
}));

gulp.task('default', gulp.series('watch'));
