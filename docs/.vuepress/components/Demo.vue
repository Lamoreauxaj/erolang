<template>
    <div class="demo">
        <div class="language- line-numbers-mode" ref="demo">
            <pre class="language-text"><code class="editor-container"><textarea ref="editor" class="editor" v-model="codeValue"/></code></pre>
            <div class="line-numbers-wrapper">
                <template v-for="k in lineNumbers" v-key="k">
                    <span class="line-number">{{k}}</span>
                    <br>
                </template>
            </div>
        </div>
        <Button @click.native="onRun">Run</Button>

        <div class="custom-block danger" v-if="error">
            <p class="custom-block-title">Error</p>
            <pre class="error-text">{{ error }}</pre>
        </div>

        <div class="custom-block tip" v-if="output">
            <p class="custom-block-title">Output</p>
            <pre class="output-text">{{ output }}</pre>
        </div>

        <Renderer v-if="output && render" :objects="renderObjects">
        </Renderer>
    </div>
</template>

<script>
import axios from 'axios'

export default {
    name: 'demo',
    props: {
        code: {
            required: false,
            type: String,
            defaultValue: undefined
        },
        render: {
            required: false,
            type: Boolean,
            default: true
        }
    },
    data() {
        return {
            codeValue: this.code,
            error: '',
            output: ''
        }
    },
    computed: {
        lineNumbers() {
            return this.codeValue.split('\n').length
        },
        editorHeight() {
            return this.lineNumbers * 23.0 + 10.0
        },
        renderObjects() {
            const lines = this.output.split('\n')
            const objects = []
            lines.forEach((line) => {
                try {
                    line = line.trim()
                    if (line[0] === '{') {
                        const object = JSON.parse(line)
                        objects.push(object)
                    }
                } catch (e) {
                }
            })
            return objects
        }
    },
    watch: {
        editorHeight(val) {
            if (this.$refs.editor) {
                this.$refs.editor.style.height = val + 'px'
            }
        },
        codeProp(val) {
            this.code = val
        }
    },
    created() {
        setTimeout(() => {
            if (this.$refs.editor)
                this.$refs.editor.style.height = this.lineNumbers * 23.0 + 10.0 + 'px'
        }, 0)
    },
    methods: {
        onRun() {
            this.output = ''
            this.error = ''
            axios.post(process.env.API + '/run', { code: this.codeValue })
                .then((response) => {
                    this.output = response.data.data
                })
                .catch((error) => {
                    this.error = error.response.data.error
                })
        }
    }
}
</script>

<style scoped>
.demo {
    display: flex;
    flex-direction: column;
    align-content: flex-start;
    justify-content: center;
}
.editor {
    background-color: #282c34;
    color: #fff;
    border: none;
    outline-width: 0;
    resize: none;
    margin: 0;
    padding: 0;
    line-height: 1.440rem;
    overflow-x: scroll;
    width: 100%;
    white-space: nowrap;
    overflow-y: hidden;
}
.editor-container {
}
.language-text {
    margin-top: 0 !important;
    margin-bottom: 0 !important;
}
.langauge- {
}
.line-numbers-wrapper {
    margin-top: -2px !important;
}
::-webkit-scrollbar {
  width: 10px;
}
::-webkit-scrollbar-track {
  background: #282c34;
}
::-webkit-scrollbar-thumb {
  background: #555;
}
::-webkit-scrollbar-thumb:hover {
  background: #444;
}
.output-text, .error-text {
    font-family: 'Courier New', Courier, monospace;
    padding: 15px 10px 15px 10px;
    margin: 0;
}
.output-text {
    background-color: #f3f5f7;
}
.error-text {
    background-color: #ffe6e6;
}
</style>