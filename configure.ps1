$content = get-content build.ninja
$content = $content -replace "^include .*\.ninja$", "include $args.ninja"
set-content build.ninja $content
