{
        'targets':
        [
                {
                        'target_name': 'clustersim',
                        'type': 'executable',
                        'dependencies': [],
                        'defines':      [],
                        'sources':
                        [
				'src/color_map.c',
				'src/color_map.h',
				'src/common.c',
				'src/common.h',
				'src/le.c',
				'src/le.h',
				'src/main.c',
				'src/render.c',
				'src/render.h',
				'src/graph.c',
				'src/graph.h',
				'src/avrami.c',
				'src/avrami.h',
				'src/test.c',
				'src/test.h',
                        ],

                        'libraries':    ['-fopenmp', '-lconfig', '-llua5.2', '-lpng' , '-ldl', '-lcheck', '-lrt', '-lgsl', '-lgslcblas'],

                        'conditions':
                        [
                                [
                                        'OS=="linux"',
                                        {
                                                'cflags': ['-std=c11', '-Wall', '-fopenmp'],
                                                'include_dirs':
                                                [
                                                        '/usr/include/lua5.2/',
                                                ],

                                        }
                                ],
                                [
                                        'TARGET=="debug"',
                                        {
                                                'cflags':               ['-O0 -g']
                                        },
                                        {
                                                'cflags':               ['-O2'],
                                        }

                                ]
                        ]
                }
        ]
}

