// Keybit8 Game - LED & Speaker Control
// LEDピン: 赤LED 8個 (1, 8, 16, 15, 0, 9, 14, 18), 緑LED 1個 (19)
// スピーカーピン: 10

class Keybit8Game {
    constructor() {
        this.port = null;
        this.reader = null;
        this.writer = null;
        this.isConnected = false;
        this.isPlaying = false;
        this.score = 0;
        this.level = 1;
        this.gameMode = 'rhythm';
        this.difficulty = 'normal';
        this.ledBrightness = 128;
        this.volume = 50;
        
        // LEDピン定義
        this.redLedPins = [1, 8, 16, 15, 0, 9, 14, 18];
        this.greenLedPin = 19;
        this.speakerPin = 10;
        
        // キーボードの視覚化用
        this.keyLabels = ['W', 'A', 'S', 'D', 'Spc', 'Shf', 'E', '1'];
        
        // レイヤーキーのインデックス（Eと1はレイヤータップキー）
        this.layerKeyIndices = [6, 7]; // E (レイヤー2), 1 (レイヤー1)
        this.layerKeyPressed = new Set(); // 現在押されているレイヤーキー
        this.keyStates = new Map(); // すべてのキーの押下状態を追跡
        
        this.init();
    }
    
    init() {
        this.setupEventListeners();
        this.setupKeyboardVisualization();
        this.updateUI();
        this.applyTheme('light');
        
        // ページ読み込み時にフォーカスを設定
        window.addEventListener('load', () => {
            document.body.focus();
        });
    }
    
    setupEventListeners() {
        document.getElementById('connectBtn').addEventListener('click', () => this.connect());
        document.getElementById('disconnectBtn').addEventListener('click', () => this.disconnect());
        document.getElementById('startBtn').addEventListener('click', () => this.startGame());
        document.getElementById('pauseBtn').addEventListener('click', () => this.pauseGame());
        document.getElementById('resetBtn').addEventListener('click', () => this.resetGame());
        
        document.getElementById('gameMode').addEventListener('change', (e) => {
            this.gameMode = e.target.value;
        });
        
        document.getElementById('difficulty').addEventListener('change', (e) => {
            this.difficulty = e.target.value;
        });
        
        document.getElementById('ledBrightness').addEventListener('input', (e) => {
            this.ledBrightness = parseInt(e.target.value);
            document.getElementById('brightnessValue').textContent = this.ledBrightness;
            if (this.isConnected) {
                this.updateLedBrightness();
            }
        });
        
        document.getElementById('volume').addEventListener('input', (e) => {
            this.volume = parseInt(e.target.value);
            document.getElementById('volumeValue').textContent = this.volume;
        });
        
        // テーマ切り替え
        const lightBtn = document.getElementById('themeLightBtn');
        const darkBtn = document.getElementById('themeDarkBtn');
        if (lightBtn && darkBtn) {
            lightBtn.addEventListener('click', () => this.applyTheme('light'));
            darkBtn.addEventListener('click', () => this.applyTheme('dark'));
        }
        
        // キーボード入力の監視（キャプチャフェーズで登録）
        // ゲーム中はレイヤー切り替えを無視して、キーの物理的な押下状態だけを検知
        // キャプチャフェーズで登録することで、他のイベントリスナーより先に処理
        
        // レイヤーキー専用のイベントリスナー（最優先で処理）
        // レイヤーキーの処理を確実にするため、専用のリスナーで処理
        const layerKeyDownHandler = (e) => {
            if (!this.isPlaying) return;
            
            const key = e.key;
            const code = e.code;
            
            // レイヤーキー（Eと1）を最優先で検知してUIを更新
            if (key.toLowerCase() === 'e' || code === 'KeyE') {
                const keyElement = document.getElementById('key-6');
                if (keyElement) {
                    // すべてのクラスをクリアしてから設定
                    keyElement.className = 'key-visual layer-active';
                    this.keyStates.set(6, true);
                    this.layerKeyPressed.add(6);
                    
                    // 強制的にインラインスタイルを適用（setTimeoutで確実に適用）
                    setTimeout(() => {
                        keyElement.style.setProperty('background', 'linear-gradient(145deg, #81c784 0%, #66bb6a 100%)', 'important');
                        keyElement.style.setProperty('box-shadow', '0 0 20px rgba(76, 175, 80, 0.8), 0 2px 4px rgba(0, 0, 0, 0.2), inset 0 1px 2px rgba(255, 255, 255, 0.8), inset 0 -1px 2px rgba(0, 0, 0, 0.1)', 'important');
                        keyElement.style.setProperty('border-top', '2px solid #a0a0a0', 'important');
                        keyElement.style.setProperty('border-left', '2px solid #a0a0a0', 'important');
                        keyElement.style.setProperty('border-bottom', '2px solid #f5f5f5', 'important');
                        keyElement.style.setProperty('border-right', '2px solid #f5f5f5', 'important');
                        
                        // 計算されたスタイルを確認
                        const computedStyle = window.getComputedStyle(keyElement);
                        console.log('Eキーが押されました - 緑色表示', {
                            classes: keyElement.classList.toString(),
                            inlineStyle: keyElement.getAttribute('style'),
                            computedBackground: computedStyle.background,
                            computedBoxShadow: computedStyle.boxShadow,
                            computedBorderTop: computedStyle.borderTop
                        });
                    }, 0);
                }
            } else if (key === '1' || code === 'Digit1') {
                const keyElement = document.getElementById('key-7');
                if (keyElement) {
                    // すべてのクラスをクリアしてから設定
                    keyElement.className = 'key-visual layer-active';
                    this.keyStates.set(7, true);
                    this.layerKeyPressed.add(7);
                    
                    // 強制的にインラインスタイルを適用（setTimeoutで確実に適用）
                    setTimeout(() => {
                        keyElement.style.setProperty('background', 'linear-gradient(145deg, #81c784 0%, #66bb6a 100%)', 'important');
                        keyElement.style.setProperty('box-shadow', '0 0 20px rgba(76, 175, 80, 0.8), 0 2px 4px rgba(0, 0, 0, 0.2), inset 0 1px 2px rgba(255, 255, 255, 0.8), inset 0 -1px 2px rgba(0, 0, 0, 0.1)', 'important');
                        keyElement.style.setProperty('border-top', '2px solid #a0a0a0', 'important');
                        keyElement.style.setProperty('border-left', '2px solid #a0a0a0', 'important');
                        keyElement.style.setProperty('border-bottom', '2px solid #f5f5f5', 'important');
                        keyElement.style.setProperty('border-right', '2px solid #f5f5f5', 'important');
                        
                        // 計算されたスタイルを確認
                        const computedStyle = window.getComputedStyle(keyElement);
                        console.log('1キーが押されました - 緑色表示', {
                            classes: keyElement.classList.toString(),
                            inlineStyle: keyElement.getAttribute('style'),
                            computedBackground: computedStyle.background,
                            computedBoxShadow: computedStyle.boxShadow,
                            computedBorderTop: computedStyle.borderTop
                        });
                    }, 0);
                }
            }
        };
        
        const layerKeyUpHandler = (e) => {
            if (!this.isPlaying) return;
            
            const key = e.key;
            const code = e.code;
            
            // レイヤーキーが離されたときの処理
            if (key.toLowerCase() === 'e' || code === 'KeyE') {
                const keyElement = document.getElementById('key-6');
                if (keyElement) {
                    // クラスとスタイルを確実にクリア
                    keyElement.className = 'key-visual';
                    setTimeout(() => {
                        keyElement.style.removeProperty('background');
                        keyElement.style.removeProperty('box-shadow');
                        keyElement.style.removeProperty('border-top');
                        keyElement.style.removeProperty('border-left');
                        keyElement.style.removeProperty('border-bottom');
                        keyElement.style.removeProperty('border-right');
                        
                        // 計算されたスタイルを確認
                        const computedStyle = window.getComputedStyle(keyElement);
                        console.log('Eキーが離されました', {
                            classes: keyElement.classList.toString(),
                            computedBackground: computedStyle.background
                        });
                    }, 0);
                    this.keyStates.set(6, false);
                    this.layerKeyPressed.delete(6);
                }
            } else if (key === '1' || code === 'Digit1') {
                const keyElement = document.getElementById('key-7');
                if (keyElement) {
                    // クラスとスタイルを確実にクリア
                    keyElement.className = 'key-visual';
                    setTimeout(() => {
                        keyElement.style.removeProperty('background');
                        keyElement.style.removeProperty('box-shadow');
                        keyElement.style.removeProperty('border-top');
                        keyElement.style.removeProperty('border-left');
                        keyElement.style.removeProperty('border-bottom');
                        keyElement.style.removeProperty('border-right');
                        
                        // 計算されたスタイルを確認
                        const computedStyle = window.getComputedStyle(keyElement);
                        console.log('1キーが離されました', {
                            classes: keyElement.classList.toString(),
                            computedBackground: computedStyle.background
                        });
                    }, 0);
                    this.keyStates.set(7, false);
                    this.layerKeyPressed.delete(7);
                }
            }
        };
        
        // キャプチャフェーズで登録（最優先）
        document.addEventListener('keydown', layerKeyDownHandler, { capture: true, passive: false });
        document.addEventListener('keyup', layerKeyUpHandler, { capture: true, passive: false });
        
        // 通常のキー処理
        document.addEventListener('keydown', (e) => {
            this.preventDefaultKeys(e);
            this.handleKeyPress(e);
        }, true);
        
        document.addEventListener('keyup', (e) => {
            this.handleKeyRelease(e);
        }, true);
    }
    
    applyTheme(mode) {
        const body = document.body;
        const lightBtn = document.getElementById('themeLightBtn');
        const darkBtn = document.getElementById('themeDarkBtn');
        
        if (mode === 'dark') {
            body.classList.add('theme-dark');
            body.classList.remove('theme-light');
            if (darkBtn) darkBtn.classList.add('theme-btn-active');
            if (lightBtn) lightBtn.classList.remove('theme-btn-active');
        } else {
            body.classList.add('theme-light');
            body.classList.remove('theme-dark');
            if (lightBtn) lightBtn.classList.add('theme-btn-active');
            if (darkBtn) darkBtn.classList.remove('theme-btn-active');
        }
    }
    
    setupKeyboardVisualization() {
        const container = document.getElementById('keyboardVisualization');
        container.innerHTML = '';
        
        this.keyLabels.forEach((label, index) => {
            const keyDiv = document.createElement('div');
            keyDiv.className = 'key-visual';
            keyDiv.id = `key-${index}`;
            // テキストは削除（デザインのみ）
            container.appendChild(keyDiv);
        });
    }
    
    async connect() {
        try {
            if (!navigator.serial) {
                alert('このブラウザはWeb Serial APIをサポートしていません。\nChrome、Edge、OperaなどのChromiumベースのブラウザを使用してください。');
                return;
            }
            
            this.port = await navigator.serial.requestPort();
            await this.port.open({ baudRate: 9600 });
            
            this.writer = this.port.writable.getWriter();
            this.reader = this.port.readable.getReader();
            
            this.isConnected = true;
            this.updateConnectionStatus(true);
            this.updateUI();
            
            // 接続確認
            await this.sendCommand('CONNECT');
            
            // データ読み取りを開始
            this.readData();
            
            console.log('Keybit8に接続しました');
        } catch (error) {
            console.error('接続エラー:', error);
            alert('接続に失敗しました: ' + error.message);
            this.isConnected = false;
            this.updateConnectionStatus(false);
            this.updateUI();
        }
    }
    
    async disconnect() {
        try {
            if (this.reader) {
                await this.reader.cancel();
                this.reader = null;
            }
            
            if (this.writer) {
                await this.writer.close();
                this.writer = null;
            }
            
            if (this.port) {
                await this.port.close();
                this.port = null;
            }
            
            this.isConnected = false;
            this.isPlaying = false;
            this.updateConnectionStatus(false);
            this.updateUI();
            
            // すべてのLEDをオフ
            await this.allLedsOff();
            
            console.log('切断しました');
        } catch (error) {
            console.error('切断エラー:', error);
        }
    }
    
    async readData() {
        try {
            while (this.isConnected && this.reader) {
                const { value, done } = await this.reader.read();
                if (done) break;
                
                // 受信データを処理
                const text = new TextDecoder().decode(value);
                console.log('受信:', text);
                this.handleReceivedData(text);
            }
        } catch (error) {
            console.error('読み取りエラー:', error);
        }
    }
    
    handleReceivedData(data) {
        // キーボードからのデータを処理
        // 例: キーが押された、LED状態など
    }
    
    async sendCommand(command) {
        if (!this.writer || !this.isConnected) {
            console.warn('キーボードに接続されていません');
            return;
        }
        
        try {
            const data = new TextEncoder().encode(command + '\n');
            await this.writer.write(data);
            console.log('送信:', command);
        } catch (error) {
            console.error('送信エラー:', error);
        }
    }
    
    // LED制御関数
    async setLed(ledIndex, state) {
        if (ledIndex < 0 || ledIndex >= this.redLedPins.length) return;
        
        const pin = this.redLedPins[ledIndex];
        const command = `LED:${pin}:${state ? 1 : 0}:${this.ledBrightness}`;
        await this.sendCommand(command);
        
        // 視覚化を更新
        const keyElement = document.getElementById(`key-${ledIndex}`);
        if (keyElement) {
            if (state) {
                keyElement.classList.add('led-on');
            } else {
                keyElement.classList.remove('led-on');
            }
        }
    }
    
    async setGreenLed(state) {
        const command = `LED:${this.greenLedPin}:${state ? 1 : 0}:${this.ledBrightness}`;
        await this.sendCommand(command);
    }
    
    async allLedsOff() {
        for (let i = 0; i < this.redLedPins.length; i++) {
            await this.setLed(i, false);
        }
        await this.setGreenLed(false);
    }
    
    async allLedsOn() {
        for (let i = 0; i < this.redLedPins.length; i++) {
            await this.setLed(i, true);
        }
    }
    
    async updateLedBrightness() {
        // 現在点灯しているLEDの明るさを更新
        // 実装は必要に応じて
    }
    
    // スピーカー制御関数
    async playTone(frequency, duration) {
        if (!this.isConnected) return;
        
        const volume = Math.floor((this.volume / 100) * 255);
        const command = `TONE:${this.speakerPin}:${frequency}:${duration}:${volume}`;
        await this.sendCommand(command);
    }
    
    async playNote(note, duration = 500) {
        // 音符名から周波数に変換
        const frequencies = {
            'C4': 262, 'D4': 294, 'E4': 330, 'F4': 349,
            'G4': 392, 'A4': 440, 'B4': 494, 'C5': 523
        };
        
        const frequency = frequencies[note] || 440;
        await this.playTone(frequency, duration);
    }
    
    // ゲーム制御
    async startGame() {
        if (!this.isConnected) {
            alert('キーボードに接続してください');
            return;
        }
        
        this.isPlaying = true;
        this.score = 0;
        this.level = 1;
        this.updateUI();
        
        // ゲーム中はフォーカスを維持してキー入力をキャプチャ
        document.body.focus();
        document.body.classList.add('game-playing');
        
        // ゲーム開始の演出
        await this.allLedsOn();
        await this.playNote('C5', 200);
        await new Promise(resolve => setTimeout(resolve, 200));
        await this.allLedsOff();
        await this.playNote('G4', 200);
        
        // ゲームモードに応じて開始
        switch (this.gameMode) {
            case 'rhythm':
                this.startRhythmGame();
                break;
            case 'typing':
                this.startTypingGame();
                break;
            case 'memory':
                this.startMemoryGame();
                break;
        }
    }
    
    pauseGame() {
        this.isPlaying = false;
        this.updateUI();
        document.body.classList.remove('game-playing');
        // 一時停止時はキー入力の制限を解除
    }
    
    async resetGame() {
        this.isPlaying = false;
        this.score = 0;
        this.level = 1;
        await this.allLedsOff();
        this.updateUI();
        document.body.classList.remove('game-playing');
        document.getElementById('gameDisplay').innerHTML = '<p>ゲームをリセットしました</p>';
        // リセット時はキー入力の制限を解除
    }
    
    // リズムゲーム
    async startRhythmGame() {
        const display = document.getElementById('gameDisplay');
        display.innerHTML = '<h2>リズムゲーム</h2><p>キーを押してリズムに合わせてください！</p>';
        
        const sequence = this.generateRhythmSequence();
        let currentIndex = 0;
        
        const gameLoop = async () => {
            if (!this.isPlaying) return;
            
            // LEDを点灯
            const ledIndex = sequence[currentIndex % sequence.length];
            await this.setLed(ledIndex, true);
            await this.playNote('C5', 100);
            
            // 一定時間後にLEDを消灯
            setTimeout(async () => {
                await this.setLed(ledIndex, false);
            }, 300);
            
            currentIndex++;
            
            if (this.isPlaying) {
                const speed = this.getGameSpeed();
                setTimeout(gameLoop, speed);
            }
        };
        
        gameLoop();
    }
    
    // タイピングゲーム
    async startTypingGame() {
        const display = document.getElementById('gameDisplay');
        display.innerHTML = '<h2>タイピングゲーム</h2><p>表示されたキーを押してください！</p>';
        
        const keys = ['W', 'A', 'S', 'D', 'Space', 'Shift', 'E', '1'];
        let currentKey = null;
        let correctCount = 0;
        
        const showNextKey = () => {
            if (!this.isPlaying) return;
            
            currentKey = keys[Math.floor(Math.random() * keys.length)];
            const keyIndex = keys.indexOf(currentKey);
            
            display.innerHTML = `<h2>タイピングゲーム</h2><p style="font-size: 3em; font-weight: bold;">${currentKey}</p>`;
            
            // 対応するLEDを点灯
            if (keyIndex < this.redLedPins.length) {
                this.setLed(keyIndex, true);
            }
        };
        
        this.currentKeyHandler = (pressedKey) => {
            if (!this.isPlaying || !currentKey) return;
            
            const keyIndex = keys.indexOf(currentKey);
            // SpaceキーとShiftキーの判定を改善
            const isMatch = pressedKey === currentKey || 
                           (currentKey === 'Space' && (pressedKey === ' ' || pressedKey === 'Space')) ||
                           (currentKey === 'Shift' && (pressedKey === 'Shift' || pressedKey === 'ShiftLeft' || pressedKey === 'ShiftRight'));
            
            if (isMatch) {
                correctCount++;
                this.score += 10;
                this.setLed(keyIndex, false);
                this.playNote('C5', 100);
                this.updateUI();
                
                if (correctCount % 10 === 0) {
                    this.level++;
                    this.playNote('G5', 200);
                }
                
                setTimeout(showNextKey, 300);
            }
        };
        
        showNextKey();
    }
    
    // メモリーゲーム
    async startMemoryGame() {
        const display = document.getElementById('gameDisplay');
        display.innerHTML = '<h2>メモリーゲーム</h2><p>LEDの順序を覚えてください！</p>';
        
        const sequence = [];
        const sequenceLength = 3 + this.level;
        
        // ランダムなシーケンスを生成
        for (let i = 0; i < sequenceLength; i++) {
            sequence.push(Math.floor(Math.random() * this.redLedPins.length));
        }
        
        // シーケンスを表示
        const showSequence = async () => {
            for (let i = 0; i < sequence.length; i++) {
                await this.setLed(sequence[i], true);
                await this.playNote('C5', 200);
                await new Promise(resolve => setTimeout(resolve, 300));
                await this.setLed(sequence[i], false);
                await new Promise(resolve => setTimeout(resolve, 200));
            }
            
            display.innerHTML = '<h2>メモリーゲーム</h2><p>同じ順序でキーを押してください！</p>';
        };
        
        await showSequence();
        
        // ユーザーの入力を待つ
        let userSequence = [];
        this.currentKeyHandler = (pressedKey) => {
            if (!this.isPlaying) return;
            
            // キーマッピングを改善（SpaceとShiftの処理を含む）
            let keyIndex = -1;
            if (pressedKey === 'W') keyIndex = 0;
            else if (pressedKey === 'A') keyIndex = 1;
            else if (pressedKey === 'S') keyIndex = 2;
            else if (pressedKey === 'D') keyIndex = 3;
            else if (pressedKey === ' ' || pressedKey === 'Space') keyIndex = 4;
            else if (pressedKey === 'Shift' || pressedKey === 'ShiftLeft' || pressedKey === 'ShiftRight') keyIndex = 5;
            else if (pressedKey === 'E') keyIndex = 6;
            else if (pressedKey === '1') keyIndex = 7;
            
            if (keyIndex !== -1) {
                userSequence.push(keyIndex);
                this.setLed(keyIndex, true);
                this.playNote('C5', 100);
                
                setTimeout(() => {
                    this.setLed(keyIndex, false);
                }, 200);
                
                // シーケンスをチェック
                if (userSequence.length === sequence.length) {
                    const isCorrect = userSequence.every((val, idx) => val === sequence[idx]);
                    if (isCorrect) {
                        this.score += 50;
                        this.level++;
                        this.playNote('G5', 300);
                        display.innerHTML = '<h2>正解！</h2><p>次のレベルに進みます...</p>';
                        setTimeout(() => this.startMemoryGame(), 2000);
                    } else {
                        this.isPlaying = false;
                        this.playNote('C4', 500);
                        display.innerHTML = '<h2>ゲームオーバー</h2><p>間違えました。リセットして再開してください。</p>';
                    }
                    userSequence = [];
                }
            }
        };
    }
    
    generateRhythmSequence() {
        return [0, 1, 2, 3, 4, 5, 6, 7];
    }
    
    getGameSpeed() {
        const speeds = {
            'easy': 1000,
            'normal': 600,
            'hard': 300
        };
        return speeds[this.difficulty] || 600;
    }
    
    preventDefaultKeys(event) {
        // ゲーム中は特定のキーのデフォルト動作を無効化
        if (this.isPlaying) {
            // Space、Arrow keys、Page Up/Downなどのスクロールキーを無効化
            const preventKeys = [
                ' ', 'Space', 'ArrowUp', 'ArrowDown', 'ArrowLeft', 'ArrowRight',
                'PageUp', 'PageDown', 'Home', 'End'
            ];
            
            if (preventKeys.includes(event.key) || preventKeys.includes(event.code)) {
                event.preventDefault();
                event.stopPropagation();
            }
        }
    }
    
    handleKeyPress(event) {
        if (!this.isPlaying) return;
        
        // ゲーム中はキー入力をキャプチャしてデフォルト動作を防ぐ
        // レイヤー切り替えは無視して、キーの物理的な押下状態だけを検知
        const key = event.key;
        const code = event.code;
        
        // キーマッピング（下段のキーも含む）
        let mappedKey = null;
        let keyIndex = -1;
        
        // 上段のキー
        if (key.toLowerCase() === 'w') {
            mappedKey = 'W';
            keyIndex = 0;
        } else if (key.toLowerCase() === 'a') {
            mappedKey = 'A';
            keyIndex = 1;
        } else if (key.toLowerCase() === 's') {
            mappedKey = 'S';
            keyIndex = 2;
        } else if (key.toLowerCase() === 'd') {
            mappedKey = 'D';
            keyIndex = 3;
        }
        // 下段のキー
        else if (key === ' ' || code === 'Space') {
            mappedKey = 'Space';
            keyIndex = 4; // Spc
        } else if (key === 'Shift' || code.startsWith('Shift')) {
            mappedKey = 'Shift';
            keyIndex = 5; // Shf
        } else if (key.toLowerCase() === 'e') {
            mappedKey = 'E';
            keyIndex = 6; // レイヤーキー（E）
        } else if (key === '1') {
            mappedKey = '1';
            keyIndex = 7; // レイヤーキー（1）
        }
        
        // UIのキーを更新（キーが押された瞬間に反映）
        // レイヤー切り替えに関係なく、物理的なキー押下を検知
        // ただし、レイヤーキー（E=6, 1=7）は専用のイベントリスナーで処理するため、ここでは処理しない
        if (keyIndex !== -1 && keyIndex !== 6 && keyIndex !== 7) {
            const keyElement = document.getElementById(`key-${keyIndex}`);
            if (keyElement) {
                // 通常キーはactiveクラス
                keyElement.classList.remove('layer-active');
                keyElement.classList.add('active');
                this.keyStates.set(keyIndex, true);
            }
        }
        
        // ゲームロジックへの通知（レイヤー切り替えは無視）
        // キーが押されたという事実だけを通知
        if (this.currentKeyHandler && mappedKey) {
            this.currentKeyHandler(mappedKey);
        }
        
        // すべてのゲーム関連キーのデフォルト動作を防ぐ
        // これにより、レイヤー切り替えによるキーイベントのキャンセルを防ぐ
        // キーリピート時（event.repeat）も確実に処理
        if (['w', 'a', 's', 'd', ' ', 'e', '1'].includes(key.toLowerCase()) || key === 'Shift' || code.startsWith('Shift')) {
            event.preventDefault();
            event.stopPropagation();
            event.stopImmediatePropagation();
        }
    }
    
    handleKeyRelease(event) {
        if (!this.isPlaying) return;
        
        const key = event.key;
        const code = event.code;
        
        let keyIndex = -1;
        
        // 上段のキー
        if (key.toLowerCase() === 'w') {
            keyIndex = 0;
        } else if (key.toLowerCase() === 'a') {
            keyIndex = 1;
        } else if (key.toLowerCase() === 's') {
            keyIndex = 2;
        } else if (key.toLowerCase() === 'd') {
            keyIndex = 3;
        }
        // 下段のキー
        else if (key === ' ' || code === 'Space') {
            keyIndex = 4; // Spc
        } else if (key === 'Shift' || code.startsWith('Shift')) {
            keyIndex = 5; // Shf
        }
        // レイヤーキー（E=6, 1=7）は専用のイベントリスナーで処理するため、ここでは処理しない
        // else if (key.toLowerCase() === 'e') {
        //     keyIndex = 6;
        // } else if (key === '1') {
        //     keyIndex = 7;
        // }
        
        // 通常キーのみ処理
        if (keyIndex !== -1) {
            const keyElement = document.getElementById(`key-${keyIndex}`);
            if (keyElement) {
                keyElement.classList.remove('active');
                this.keyStates.set(keyIndex, false);
            }
        }
    }
    
    updateConnectionStatus(connected) {
        const statusIndicator = document.querySelector('.status-indicator');
        const statusText = document.getElementById('statusText');
        
        if (connected) {
            statusIndicator.classList.remove('disconnected');
            statusIndicator.classList.add('connected');
            statusText.textContent = '接続済み';
        } else {
            statusIndicator.classList.remove('connected');
            statusIndicator.classList.add('disconnected');
            statusText.textContent = '未接続';
        }
    }
    
    updateUI() {
        document.getElementById('score').textContent = this.score;
        document.getElementById('level').textContent = this.level;
        
        document.getElementById('connectBtn').disabled = this.isConnected;
        document.getElementById('disconnectBtn').disabled = !this.isConnected;
        document.getElementById('startBtn').disabled = !this.isConnected || this.isPlaying;
        document.getElementById('pauseBtn').disabled = !this.isConnected || !this.isPlaying;
        document.getElementById('resetBtn').disabled = !this.isConnected;
    }
}

// ゲームを初期化
const game = new Keybit8Game();

