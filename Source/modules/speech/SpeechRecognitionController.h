/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SpeechRecognitionController_h
#define SpeechRecognitionController_h

#include "core/page/Page.h"
#include "modules/speech/SpeechRecognitionClient.h"
#include "wtf/PassOwnPtr.h"

namespace blink {

class MediaStreamTrack;

class SpeechRecognitionController final
    : public NoBaseWillBeGarbageCollectedFinalized<SpeechRecognitionController>
    , public WillBeHeapSupplement<LocalFrame> {
    WILL_BE_USING_GARBAGE_COLLECTED_MIXIN(SpeechRecognitionController);
public:
    virtual ~SpeechRecognitionController();

    void start(SpeechRecognition* recognition, const SpeechGrammarList* grammars, const String& lang, bool continuous, bool interimResults, unsigned long maxAlternatives, MediaStreamTrack* audioTrack)
    {
        m_client->start(recognition, grammars, lang, continuous, interimResults, maxAlternatives, audioTrack);
    }

    void stop(SpeechRecognition* recognition) { m_client->stop(recognition); }
    void abort(SpeechRecognition* recognition) { m_client->abort(recognition); }

    static const char* supplementName();
    static void provideTo(LocalFrame&, PassOwnPtr<SpeechRecognitionClient>);
    static SpeechRecognitionController* from(LocalFrame&);

    void trace(Visitor*) override;

private:
    explicit SpeechRecognitionController(PassOwnPtr<SpeechRecognitionClient>);

    OwnPtr<SpeechRecognitionClient> m_client;
};

} // namespace blink

#endif // SpeechRecognitionController_h
